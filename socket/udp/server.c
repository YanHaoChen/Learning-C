#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <time.h>

#define PortNumber 5555

int main(){
	struct sockaddr_in address;
	int sock, byte_recv;
	char buffer[50];

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) printf("Error creating socket\n");

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(PortNumber);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *)&address, sizeof(address))== -1){
		printf("error binding\n");
		close(sock);
	}
	int address_length = sizeof(address);
	int sizeCount = 0;
	int dataframCount = 0;
	clock_t t1, t2;
	t1 = clock();
	for(;;){
		byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, &address_length);
		if(byte_recv < 0) printf("Error recving packet\n");
		dataframCount++;
		int i = 0;
		for (i=0;i<50;i++){
			if(buffer[i] == '\0'){
				sizeCount += i + 1;
				break;
			}
		}

		if (buffer[0] == '\0') {
			t2 = clock();
			printf("Client send completed!\n");
			printf("Datagram number: %d\n", dataframCount);
			printf("Time interval: %lf sec\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
			printf("Throughput: %lf Mbps\n",(sizeCount/((t2-t1)/(double)(CLOCKS_PER_SEC)))/1000);
			return 0;
		}
	}
}
