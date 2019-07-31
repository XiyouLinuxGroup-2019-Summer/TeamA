#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void assisthread(void *arg)
{
    printf("i am helping to do some jobs\n");
    sleep(3);
    pthread_exit(0);
}

int main()
{
    pthread_t  assistthid;
    int status;

    pthread_create(&assistthid,NULL,(void *)assisthread,NULL);
    pthread_join(assistthid,(void *)&status);
    printf("assistthid is exit caused %d\n",status);

    return 0;
}
