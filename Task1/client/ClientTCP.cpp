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
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

#define PORT 5555
#define IP_ADDR "127.0.0.1"
#define BUF_SIZE 1024

#ifdef _WIN32

    SOCKET clientSocket;

    std::string getTCP ()
    {
        char buf[BUF_SIZE] = {0};
        int bytesReceived = recv(clientSocket, buf, BUF_SIZE, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
            return "err";
        }
        std::string buffer (buf);
        return buffer;
    }

    int sendTCP(std::string str)
    {
        if ( send(clientSocket, str.c_str(), strlen(str.c_str()), 0) == SOCKET_ERROR)
        {
            std::cerr << "Send failed\n";
            return -1;
        }
        else
            return 0;
    }

    void startClient()
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
        {
            std::cerr << "WSAStartup failed." << std::endl;
            return;
        }

        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET) 
        {
            std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
        serverAddr.sin_port = htons(PORT);

        if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) 
        {
            std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return;
        }
    }

    void stopClient()
    {
        closesocket(clientSocket);
        WSACleanup();
    }

#endif

#ifdef __linux__

    char SERVER_ADDRESS[] = IP_ADDR;
    int clientSocket;
    struct sockaddr_in serverAddress;

    std::string getTCP ()
    {
        char buf[BUF_SIZE] = {0};
        int bytesReceived = recv(clientSocket, buf, BUF_SIZE, 0);
        if (bytesReceived < 0) 
        {
            std::cerr << "Receive failed\n";
             return "err";
        }
        else
        {
            std::string buffer (buf);
            return buffer;
        }

    }

    int sendTCP(std::string str)
    {
        const char *message = str.c_str();
        if (send(clientSocket, message, strlen(message), 0) < 0) 
        {
            std::cerr << "Send failed\n";
            return -1;
        }
        else
            return 0;
    }

    void startClient()
    {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) 
        {
            std::cerr << "Error creating socket\n";
            return;
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);

        if (inet_pton(AF_INET, SERVER_ADDRESS, &serverAddress.sin_addr) <= 0)
        {
            std::cerr << "Invalid address\n";
            return;
        }

        if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Connection failed\n";
            return;
        }
        else
            std::cout << "Connected to server\n";
    }

    void stopClient()
    {
        close(clientSocket);
    }

#endif
