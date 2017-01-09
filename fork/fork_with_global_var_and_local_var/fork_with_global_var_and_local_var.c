#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int idata = 111;

int main() {

	int istack = 222;
	pid_t childPid;

	switch(childPid = fork()){
		case -1:
			exit(0);
		case 0:
			idata += 20;
			istack += 20; 
			break;		
		default:
			wait(NULL);
			break;
	}	
	printf("PID=%ld %s idata=%d istack=%d\n",(long)getpid(),(childPid==0)?"(child)":"(parent)",idata,istack);
	exit(EXIT_SUCCESS);
}
