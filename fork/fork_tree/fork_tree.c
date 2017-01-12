#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t b_child, d_child, e_child;
	long int a;

	a = (long)getpid();

	switch(b_child = fork()){
		case -1:
			exit(0);
		case 0:
			printf("I'm b. PID=%ld My parent is=%ld \n",(long)getpid(),a);
			pid_t c,f;
			long int b;
			b = (long)getpid();
			switch (c = fork()) {
				case -1:
					exit(0);
				case 0:
					printf("I'm c. PID=%ld My parent is=%ld \n",(long)getpid(),b);
					return 0;
				default:
					wait(NULL);
					break;
			}

			switch (f = fork()) {
				case -1:
					exit(0);
				case 0:
					printf("I'm f. PID=%ld My parent is=%ld\n",(long)getpid(),b);
					pid_t g;
				 	long int f;
					f = (long)getpid();

					switch (g = fork()) {
						case -1:
							exit(0);
						case 0:
							printf("I'm g. PID=%ld My parent is=%ld\n",(long)getpid(),f);
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
			return 0;

		default:
			wait(NULL);
			break;
	}

	switch(d_child = fork()){
		case -1:
			exit(0);
		case 0:
			printf("I'm d. PID=%ld My parent is=%ld\n",(long)getpid(),a);
			return 0;
		default:
			wait(NULL);
			break;
	}

	switch(e_child = fork()){
		case -1:
			exit(0);
		case 0:
			printf("I'm e. PID=%ld My parent is=%ld\n",(long)getpid(),a);
			return 0;
		default:
			wait(NULL);
			break;
	}


	printf("PID=%ld %s\n",(long)getpid(),"I'm a.");
	exit(EXIT_SUCCESS);
	return 0;
}
