#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

static int clientArray[100];

int main(){
	int sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	socklen_t len;
	int sock_client;

	sock0 = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock0, (struct sockaddr*)&addr, sizeof(addr));
	//printf("binding...\n");

	listen(sock0, 5);
	//printf("listening\n");
	len = sizeof(client);
	struct timeval tv;
	fd_set readfds;
	fd_set temp_set;
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_ZERO(&temp_set);
	FD_SET(sock0, &readfds);
	
	int client_count = 0;
	
	
	while(1){
		FD_ZERO(&temp_set);
		temp_set = readfds;	
		select(101, &temp_set, NULL, NULL, &tv);
		if(FD_ISSET(sock0, &temp_set)){
			sock_client = accept(sock0, (struct sockaddr*)&client, &len);
			printf("\tClient%d connect\n",client_count);
			FD_SET(sock_client, &readfds);
			clientArray[client_count]=sock_client;
			client_count++;
		} else {
			int j;
			for(j=0;j<100;j++){
				if(FD_ISSET(clientArray[j], &readfds) && clientArray[j] != sock0){
					char buf[50];
					memset(buf, 0, sizeof(buf));
					read(clientArray[j],buf, sizeof(buf));
					//FD_SET(clientArray[j], &readfds);
					printf("\t%s\n",buf);
					char output[100];
					memset(output, 0, sizeof(output));
					sprintf(output, "Client%d:%s", j, buf);
					int i;
					for(i=0;i<100;i++){
						if(clientArray[i] != 0 && clientArray[i] != clientArray[j]){
							write(clientArray[i],output, sizeof(output));	
						}
					}	
				}
			}
		}	
	}
	return 0;
}
