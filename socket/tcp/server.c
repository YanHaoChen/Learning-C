#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PortNumber 5555

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr,client_addr;
    int sock, byte_recv, server_addr_length = sizeof(server_addr), client_addr_length=sizeof(client_addr), recfd;
    char buffer[50];
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)    printf("Error creating socket\n");
    bzero(&server_addr, server_addr_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PortNumber);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock,(struct sockaddr *)&server_addr, server_addr_length) == -1) {
        printf("error binding!\n");
        close(sock);
    }
    if (listen(sock, 20) == -1) {
        printf("listen failed!\n");
        close(sock);
    }
    int sizeCount = 0;
	int dataframCount = 0;
	clock_t t1, t2;
    if((recfd = accept(sock,(struct sockaddr *)&client_addr,&client_addr_length))==-1) {
        printf("accept failed!\n");
        close(sock);
    } else {
        t1 = clock();
        for (;;) {
            byte_recv = recv(recfd, buffer, sizeof(buffer),0);

            if (byte_recv < 0)    printf("Error recving packet\n");
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
    			printf("segment number: %d\n", dataframCount);
    			printf("Time interval: %lf sec\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
    			printf("Throughput: %lf Mbps\n",(sizeCount/((t2-t1)/(double)(CLOCKS_PER_SEC)))/1000);
    			return 0;
    		}
      }
    }

}
