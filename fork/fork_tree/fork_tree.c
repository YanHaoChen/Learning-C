#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t b_child, d_child, e_child;
	char *a;
	a = "My parent is a.";

	switch(b_child = fork()){
		case -1:
			exit(0);
		case 0:
			printf("I'm b. PID=%ld %s \n",(long)getpid(),a);
			pid_t c,f;
			char *b;
			b = "My parent is b.";
			switch (c = fork()) {
				case -1:
					exit(0);
				case 0:
					printf("I'm c. PID=%ld %s \n",(long)getpid(),b);
					return 0;
				default:
					wait(NULL);
					break;
			}

			switch (f = fork()) {
				case -1:
					exit(0);
				case 0:
					printf("I'm f. PID=%ld %s\n",(long)getpid(),b);
					return 0;
				default:
					wait(NULL);
					break;
			}
			return 0;

		default:
			wait(NULL);
			break;
	}

	switch(d_child = fork()){
		case -1:
			exit(0);
		case 0:
			printf("I'm d. PID=%ld %s\n",(long)getpid(),a);
			return 0;
		default:
			wait(NULL);
			break;
	}

	switch(e_child = fork()){
		case -1:
			exit(0);
		case 0:
			printf("I'm e. PID=%ld %s\n",(long)getpid(),a);
			pid_t g;
			char *e;
			e = "My parent is e.";
			switch (g = fork()) {
				case -1:
					exit(0);
				case 0:
					printf("I'm g. PID=%ld %s\n",(long)getpid(),e);
					return 0;
				default:
					wait(NULL);
					return 0;
					break;
			}
		default:
			wait(NULL);
			break;
	}


	printf("PID=%ld %s\n",(long)getpid(),"I'm a.");
	exit(EXIT_SUCCESS);
	return 0;
}
