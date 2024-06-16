#include <iostream>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <set>

std::set<std::string> getLocalIps();

void printNetworkBytes();

int printIpHeader(unsigned char* buffer);
