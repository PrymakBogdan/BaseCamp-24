#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "SendHDDInfo.h"
#include "ServerTCP.h"

int main() {
    startServer();
    startSend();
    stopServer();
    return 0;
}
