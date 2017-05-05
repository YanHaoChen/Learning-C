#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

static int clientArray[100];
static int client_count = 0;
void *connectWithClient(void *arg){
	while(1) {
		char buf[50];
		memset(buf, 0, sizeof(buf));
		read(clientArray[(int)arg], buf, sizeof(buf));
		printf("\t%s\n", buf);
		char output[100];
		memset(output, 0, sizeof(output));
		sprintf(output, "Client%d:%s", (int)arg, buf);
		int i;
		for(i=0;i<100;i++){
			if(clientArray[i]!=0 && i != (int)arg){
				write(clientArray[i], output, sizeof(output));
			}
		}
	}	
}

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

	while(1){
		sock_client = accept(sock0, (struct sockaddr*)&client, &len);
		clientArray[client_count] = sock_client;
		printf("\tClient%d connect\n",client_count);
		int rc;
		pthread_t thread;
		rc = pthread_create(&thread, NULL, connectWithClient,(void *)client_count);
		client_count++;		
		if(rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	return 0;
}
