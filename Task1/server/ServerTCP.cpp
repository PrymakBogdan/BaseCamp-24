#include <iostream>
#include <stdio.h>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <iostream>

    #pragma comment(lib, "Ws2_32.lib")
#endif

#ifdef __linux__
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

#define PORT 5555
#define BUF_SIZE 1024

#ifdef _WIN32

    SOCKET serverSocket;
    SOCKET clientSocket;

    int sendTCP(const std::string & message)
    {
        if (send(clientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
        {
            std::cout << "Send failed\n";
            return -1;
        }
        else
            return 0;
    }

    std::string getTCP()
    {
        char buf[BUF_SIZE];

        int bytesReceived = recv(clientSocket, buf, BUF_SIZE, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
            return 0;
        }
        else
        {
            std::string buffer (buf);
            return buffer;
        }

    }

    void startServer()
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed." << std::endl;
            return;
        }

        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(PORT);

        if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "Waiting for client connection..." << std::endl;

        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "Client connected." << std::endl;
    }

    void stopServer()
    {
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
    }
#endif

#ifdef __linux__

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    void sendTCP( const std::string & message)
    {

        if (write(clientSocket, message.c_str(), strlen(message.c_str())) < 0)
        {
            std::cerr << "SendTCP failed\n";
        }
    }

    std::string getTCP()
    {
        char buf[BUF_SIZE];
        int bytes_received = read(clientSocket, buf, BUF_SIZE);
        std::string buffer (buf);
        if (bytes_received < 0) {
            std::cerr << "GetTCP failed\n";
        }
        return buffer;
    }

    void startServer()
    {

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) 
        {
            std::cerr << "Error creating socket\n";
            return;
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(PORT);
        
        if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Bind failed\n";
            return;
        }

        if (listen(serverSocket, 3) < 0) {
            std::cerr << "Listen failed\n";
            return;
        }

        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Accept failed\n";
            return;
        }
        else
            std::cout << "Connected\n";

    }

    void stopServer()
    {
        close(clientSocket);
        close(serverSocket);
    }

#endif
