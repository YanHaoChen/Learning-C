#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

static int a=0;
static sem_t sem;

void *counter_thread(void *arg) {
    printf("Thread ID:%lu\n", pthread_self());
    printf("Argument:%d\n", (int)arg);
    int i=0;
    for(i=0;i<250000;i++){
        sem_wait(&sem);
        a++;
        sem_post(&sem);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1,t2,t3,t4;
    int t = 1;
    if (sem_init(&sem, 0, 1)== -1){
        printf("err");
        exit (1);
    }


    pthread_create(&t1, NULL, counter_thread, (void *)t);
    pthread_create(&t2, NULL, counter_thread, (void *)t);
    pthread_create(&t3, NULL, counter_thread, (void *)t);
    pthread_create(&t4, NULL, counter_thread, (void *)t);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    printf("Value= %d\n", a);
    sem_destroy(&sem);
    return 0;
}
