#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "ClientTCP.h"

int main() {
    startClient();
    std::cout<<"\n PC Name \t| HDD size \t| Free space\n";

    while (true)
    {
        std::string mess;

        mess = getTCP();
        if (mess == "err")
        {
            break;
        }
        else
        {
            std::cout << mess;
        }
        std::cout <<"\t| " ;
        sendTCP("1");

        mess = getTCP();
        if (mess == "err")
        {
            break;
        }
        else
        {
            std::cout <<mess;
        }
        std::cout <<"\t| " ;
        sendTCP("1");

        mess = getTCP();
        if (mess == "err")
        {
            break;
        }
        else
            std::cout<< mess<<"\n";
    }

    #ifdef _WIN32
        std::system("pause");
    #endif

    stopClient();
    return 0;
}
