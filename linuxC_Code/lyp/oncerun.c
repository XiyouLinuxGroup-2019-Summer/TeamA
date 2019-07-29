#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
    printf("fuction run is running in thread %lu\n",pthread_self());
}

void *thread1(void *arg)
{
    pthread_t thid = pthread_self();
    printf("current thread1's ID is %lu\n",thid);
    pthread_once(&once,run);
    printf("thread1 ends\n");
}

void *thread2(void *arg)
{
    pthread_t thid = pthread_self();
    printf("current thread2's ID is %lu\n",thid);
    pthread_once(&once,run);
    printf("thread2 ends\n");
}

int main()
{
    pthread_t thid,thid1,thid2;

    printf("main thread ID is %lu\n",pthread_self());

    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(1);
    printf("main thread exit!\n");

    return 0;
}

