#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <time.h>

#define Server_PortNumber 5555
#define Server_Address "127.0.0.1"

int main(){
	struct sockaddr_in address;
	int sock, byte_sent;
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) printf("Error creating socket\n");

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(Server_PortNumber);
	address.sin_addr.s_addr = inet_addr(Server_Address);

	int address_length = sizeof(address);
	char stop_buffer[1]="\0";
	char buffer[6]="hello\0";
	clock_t t1, t2;
	double sizeCount=0.0;
	t1 = clock();
	int i = 0;
	for(i=0;i < 59; i++) {
		byte_sent = send(sock, buffer, sizeof(buffer), 0);
		if (byte_sent < 0)    printf("Error recving packet\n");
		sizeCount +=6;
	}
	byte_sent = send(sock, stop_buffer, sizeof(stop_buffer), 0);
	t2 = clock();
	sizeCount +=1;
	close(sock);
	printf("Server IP: %s\n", Server_Address);
	printf("Datagram number: 60\n");
	printf("Time interval: %lf sec\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
	printf("Throughput: %lf Mbps\n",(sizeCount/((t2-t1)/(double)(CLOCKS_PER_SEC)))/1000);

	return 0;
}
