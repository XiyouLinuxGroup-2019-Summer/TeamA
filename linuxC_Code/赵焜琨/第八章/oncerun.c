#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_once_t once = PTHREAD_ONCE_INIT;
void run(void)
{
    printf("fuction run is running in thread %lu\n",pthread_self());
}

void *thread1(void *arg)
{
    pthread_t thid = pthread_self();
    printf("current thread1 id = %lu\n",thid);
    pthread_once(&once,run);
    printf("thread1 is end\n");
}

void *thread2(void *arg)
{
    pthread_t thid = pthread_self();
    printf("current thread2 id = %lu\n",thid);
    pthread_once(&once,run);
    printf("thread2 is end\n");
}

int main()
{
    pthread_t thid1,thid2;
    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(3);
    printf("main thread exit\n");
    exit(0);
}
