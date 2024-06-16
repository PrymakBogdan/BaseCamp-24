#include <sys/socket.h>
#include "getInfo.h"
#define bufSize 65536

int main()
{
   int sockRaw;
   struct sockaddr saddr;
   unsigned char *buffer = (unsigned char *)malloc(bufSize);
   int saddrSize, dataSize;

   unsigned long long totalNet = 0;
   long long dataSended = 0;
   long long dataResieved = 0;

   sockRaw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
   if (sockRaw < 0) 
   {
       perror("Socket Error");
       return 1;
   }

   while (true)
   {
       saddrSize = sizeof(saddr);

       dataSize = recvfrom(sockRaw, buffer, bufSize, 0, &saddr, (socklen_t*)&saddrSize);
       if (dataSize < 0) 
       {
           perror("Recvfrom Error");
           return 1;
       }

       int p = printIpHeader(buffer);

       if (p == 1)
       {
           dataSended += dataSize;
       }
       else
       if (p == 2)
       {
           dataResieved += dataSize;
       }

       totalNet += dataResieved + dataSended;

       printNetworkBytes();
       printf("From program start");
       printf("\n  Data Size: \t %i", dataSize);
       printf("\n  Data Sended: \t %lld", dataSended);
       printf("\n  Data Rcv: \t %lld", dataResieved);
       printf("\n  Total: \t %llu", totalNet);
       printf("\n============================================\n");
   }

   close(sockRaw);
   return 0;
}
