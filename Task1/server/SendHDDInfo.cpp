#include "SendHDDInfo.h"
#include "ServerTCP.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_TIME 5000
#endif

#ifdef __linux__
    #include <sys/statvfs.h>
    #include <pthread.h>
    #include <unistd.h>
    #define SLEEP_TIME 5
#endif

#define PORT 5555
#define GB 1073741824

#ifdef _WIN32

    int whileFun = 0;

    DWORD WINAPI startWhileWIN(LPVOID lpParam)
    {
        while (whileFun == 0)
        {
            std::cout<<"\n________________________";
            Sleep(SLEEP_TIME);
            sendInfoHDD();
        }
        return 0;
    }

    void startSend()
    {
        HANDLE thread = CreateThread( NULL, 0, startWhileWIN, NULL, 0, NULL);

        if (thread == NULL) {
        std::cerr << "Failed to create thread\n";
        }

        std::cout << "Enter number to stop";
        std::cin >> whileFun;
        WaitForSingleObject(thread, INFINITE);

        if (whileFun != 0)
            CloseHandle(thread);
    }

    void sendInfoHDD()
    {
        ULARGE_INTEGER Free;
        ULARGE_INTEGER Total;
        ULARGE_INTEGER TotalFree;

        GetDiskFreeSpaceEx(NULL, &Free, &Total, &TotalFree);

        std::cout << "\nFree: " << (double) Free.QuadPart / GB;
        std::cout << "\nTotal: " << (double) Total.QuadPart / GB;
        std::cout << "\n";


        char computerName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(computerName);
        if (GetComputerNameA(computerName, &size)) 
        {
            std::string str(computerName);
            sendTCP (str);
        } 
        else 
        {
            std::cerr << "Error getting computer name" << std::endl;
            return;
        }

        getTCP();

        std::string sendInfo = std::to_string((double)Free.QuadPart / GB);
        sendTCP(sendInfo);

        getTCP();

        sendInfo = std::to_string((double) Total.QuadPart / GB);
        sendTCP(sendInfo);

    }

#endif

#ifdef __linux__

    int whileFun = 0;

    void* startWhileLinux(void* a)
    {
        while (whileFun == 0)
        {
            std::cout<<"\n________________________";
            sleep(SLEEP_TIME);
            sendInfoHDD();
        }
        return NULL;
    }

    void startSend()
    {

        pthread_t threadId;

        int res = pthread_create(&threadId, NULL, startWhileLinux, NULL);
        if (res != 0)
        {
            std::cerr << "Error creating thread" << std::endl;
        }

        std::cout << "Enter number to stop";
        std::cin >> whileFun;
        if (whileFun != 0)
        {
            res = pthread_join(threadId, NULL);
            if (res != 0) {
                std::cerr << "Error joining thread" << std::endl;
            }
        }
    }

    void sendInfoHDD()
    {
        struct statvfs vfs;

        if (statvfs(".", &vfs) == -1)
            std::cerr<< "errror";
        else
        {
            std::cout << "\nbavail * frsize =" << (double) vfs.f_bavail * vfs.f_frsize  / GB;
            std::cout << "\nblocks * frsize =" << (double) vfs.f_blocks * vfs.f_frsize / GB ;
            std::cout << "\n";
            std::string sendInfo = std::to_string((double) vfs.f_blocks * vfs.f_frsize  / GB);

            char hostname[256];
            if (gethostname(hostname, sizeof(hostname)) == 0) 
            {
                std::string str(hostname);
                sendTCP (str);
            } 
            else 
            {
                std::cerr << "Error getting hostname" << std::endl;
                return;
            }

            getTCP();

            sendTCP(sendInfo);

            getTCP();

            sendInfo = std::to_string((double)vfs.f_bavail * vfs.f_frsize  / GB);
            sendTCP(sendInfo);
        }

    }
#endif
