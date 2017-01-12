#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int global= 10;

void *counter_thread(void *arg) {
    global++;
	int local = (int)arg;
    local++;
	printf("thread: global= %d,local= %d\n", global,local);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1;
    int local = 10;
	
    pthread_create(&t1, NULL, counter_thread, (void *)local);

    pthread_join(t1, NULL);

    printf("main: global= %d,local= %d\n", global,local);
    return 0;
}
