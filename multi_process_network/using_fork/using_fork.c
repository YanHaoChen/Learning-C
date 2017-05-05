#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <string.h>

static int *glob_var;
static int *who_tell;
static int *telling;
static int *last_fork;
static char *all_other_message;
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

	int user_count = 0;
	glob_var = mmap(NULL, sizeof(*glob_var)*100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	who_tell = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	telling = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	last_fork = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	all_other_message = (char *)mmap(NULL, sizeof(char)*100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	memset(glob_var, 0, sizeof(*glob_var)*100);
	memset(all_other_message,0, sizeof(char)*100);
	*who_tell = 0;
	*telling = 0;
	*last_fork = 0;
	
	while(1){
		sock_client = accept(sock0, (struct sockaddr*)&client, &len);
		pid_t childPid;
		printf("\tClient%d connect\n",user_count);
		int who_am_i = user_count;
		glob_var[who_am_i]= sock_client;
		*last_fork = user_count;
		user_count++;
		switch(childPid = fork()){
			case -1:
				exit(0);
			case 0:
				switch(fork()){
					case -1:
						exit(0);
					case 0:
						while(1){
							if(who_am_i == *last_fork && *telling == 1){
								int i;
								for(i=0;i<100;i++){
									if(glob_var[i] !=0 && i != *who_tell ){
										write(glob_var[i], all_other_message, sizeof(char)*100);
									}			
								}
								*telling = 0;
							}
						}
						break;
					default:
						while(1){
							char buf[32];
							memset(buf, 0, sizeof(buf));
							read(glob_var[who_am_i], buf, sizeof(buf));
							printf("\t%s\n", buf);
							*who_tell = who_am_i;
							*telling = 1;
							memset(all_other_message,0 ,sizeof(char)*100);
							sprintf(all_other_message, "Client%d:%s",who_am_i, buf);
						}
						break;
				}
				break;		
			default:
				break;
		}	
	}
	munmap(glob_var, sizeof(*glob_var)*100);
	return 0;
}
