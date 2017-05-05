#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <pthread.h> 
  

void *telltoServer(void *arg){
	while(1){
		char buf[50];
		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		write((int)arg, buf, sizeof(buf));		
	}
}

int main()  
{  
  struct sockaddr_in server;  
  int sock;  
  int n;  
  
  /* 製作 socket */  
  sock = socket(AF_INET, SOCK_STREAM, 0);  
  
  /* 準備連線端指定用的 struct 資料 */  
  server.sin_family = AF_INET;  
  server.sin_port = htons(5555);  
  
  /* 127.0.0.1 是 localhost 本機位址 */  
  inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);  
  
  /* 與 server 端連線 */  
  connect(sock, (struct sockaddr *)&server, sizeof(server));  
  pthread_t thread;
  int rc;
  rc = pthread_create(&thread, NULL, telltoServer,(void*)sock);
  /* 從伺服器接受資料 */  
  	int sock_id = sock;
	while(1){
		char buf[100];
		read(sock_id, buf, sizeof(buf));
		printf("%s\n",buf);				
	}

  /* 結束 socket */  
  close(sock);  
  return 0;  
}  
