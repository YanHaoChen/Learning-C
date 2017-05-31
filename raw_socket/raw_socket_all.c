#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<stdio.h> 
#include<stdlib.h>  
#include<string.h>   
 
#include<netinet/ip_icmp.h>  
#include<netinet/udp.h>   
#include<netinet/tcp.h> 
#include<netinet/ip.h>  
#include<netinet/if_ether.h> 
#include<net/if.h>
#include<net/ethernet.h> 
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
 
void ProcessPacket(unsigned char* , int);
 
struct sockaddr_in source,dest;
int ip_counter=0,arp=0,rarp=0, tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j; 
 
int main()
{
    int saddr_size , data_size;
    struct sockaddr saddr;
         
    unsigned char *buffer = (unsigned char *) malloc(65536); 
     
    printf("Starting...\n");
     
    int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
     
    if(sock_raw < 0)
    {
        perror("Socket Error");
        return 1;
    }

    	struct ifreq ifr;

	strncpy(ifr.ifr_name, "eth0", 5);

	if(ioctl(sock_raw,SIOCGIFFLAGS,&ifr) == -1)

	{	

		perror("ioctl");exit(1);

	}

	ifr.ifr_flags |= IFF_PROMISC;

	if(ioctl(sock_raw, SIOCSIFFLAGS, &ifr) == -1)
	{

		perror("ioctl");exit(3);

	}

	
    while(1)
    {
        saddr_size = sizeof saddr;
        data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            return 1;
        }
        ProcessPacket(buffer , data_size);
    }
    close(sock_raw);
    printf("Finished");
    return 0;
}
 
void ProcessPacket(unsigned char* buffer, int size)
{
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    ++total;
	struct ether_header *peth = (struct ether_header *)buffer;
    switch (iph->protocol) 
    {
        case 1: 
            ++icmp;
            break;
         
        case 2:  
            ++igmp;
            break;
         
        case 6:  
            ++tcp;
            break;
         
        case 17: 
            ++udp;
            break;
         
        default: 
            break;
    }

	switch(ntohs(peth->ether_type)){
		case 0x0800:
			++ip_counter;
			break;
		case 0x0806:
			++arp;
			break;
		case 0x8035:
			++rarp;
			break;
	}
	printf("-----statistic-----\n");
	printf("IP     :%d\n",ip_counter);
	printf("ARP    :%d\n",arp);
	printf("RARP   :%d\n",rarp);
	printf("TCP    :%d\n",tcp);
	printf("UDP    :%d\n",udp);
	printf("ICMP   :%d\n",icmp);
	printf("IGMP   :%d\n",igmp);
	printf("-----finish-----\n");
}