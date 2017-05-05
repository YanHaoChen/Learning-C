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

void *connectWithClient(void *arg){

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
		pid_t childPid;
		printf("\tClient%d connect\n",user_count);
	}
	return 0;
}
