#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
 
  
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
  
  /* 從伺服器接受資料 */  
  	int sock_id = sock;
	pid_t childPid;
	switch(childPid = fork()){
		case -1:
			exit(0);
		case 0:
			while(1){
				char output[32];
				
				memset(output, 0, sizeof(output));
				scanf("%s",output);
				write(sock_id, output, sizeof(output));		
			}
			break;
		default:
			while(1){
				char buf[100];
				read(sock_id, buf, sizeof(buf));
				printf("%s\n",buf);				
			}
			break;
	}

  /* 結束 socket */  
  close(sock);  
  return 0;  
}  
