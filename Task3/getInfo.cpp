#include "getInfo.h"

std::set<std::string> getLocalIps() 
{
   std::set<std::string> local_ips;
   struct ifaddrs *ifaddr, *ifa;
   char host[NI_MAXHOST];

   if (getifaddrs(&ifaddr) == -1)
   {
       perror("getifaddrs");
       return local_ips;
   }

   for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
   {
       if (ifa->ifa_addr == nullptr) continue;

       int family = ifa->ifa_addr->sa_family;
       if (family == AF_INET) 
       {
            if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST) == 0)
            {
               local_ips.insert(host);
            }
       }
   }

   freeifaddrs(ifaddr);
   return local_ips;
}


void printNetworkBytes()
{
   FILE *file = fopen("/proc/net/dev", "r");
   if (!file)
   {
       perror("Failed to open /proc/net/dev");
       return;
   }

   char line[256];

   fgets(line, sizeof(line), file);
   fgets(line, sizeof(line), file);

   while (fgets(line, sizeof(line), file))
   {
        char interface_name[32];
        unsigned long rx_bytes, tx_bytes;

        char *token = strtok(line, " ");
        int field = 0;
        
        while (token != NULL)
        {
            if (field == 0)
            {
                strncpy(interface_name, token, sizeof(interface_name));
                char *colon = strchr(interface_name, ':');
                if (colon)
                {
                    *colon = '\0';
                }
            } 
            else if (field == 1)
            {
                rx_bytes = strtoul(token, NULL, 10);
            } 
            else if (field == 9)
            {
                tx_bytes = strtoul(token, NULL, 10);
                break;
            }
            token = strtok(NULL, " ");
            field++;
        }

        printf("Interface:\t %s\n", interface_name);
        printf("  RX Bytes:\t %lu\n", rx_bytes);
        printf("  TX Bytes:\t %lu\n", tx_bytes);
        printf("  Total Bytes:\t %lu\n", tx_bytes + rx_bytes);
        printf("\n");
   }

   fclose(file);
}

int printIpHeader(unsigned char* buffer)
{
   std::set<std::string> local_ips = getLocalIps();

   struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
   struct sockaddr_in source, dest;
   memset(&source, 0, sizeof(source));
   memset(&dest, 0, sizeof(dest));
   source.sin_addr.s_addr = iph->saddr;
   dest.sin_addr.s_addr = iph->daddr;


   std::string source_ip = inet_ntoa(source.sin_addr);
   std::string dest_ip = inet_ntoa(dest.sin_addr);


   if (local_ips.find(source_ip) != local_ips.end())
   {
       printf("Packet Sent\n");
       return 1;
   } 
   else if (local_ips.find(dest_ip) != local_ips.end())
   {
       printf("Packet Received\n");
       return 2;
   } 
   else
   {
       printf("Packet Neither Sent Nor Received Locally\n");
       return 0;
   }
}
