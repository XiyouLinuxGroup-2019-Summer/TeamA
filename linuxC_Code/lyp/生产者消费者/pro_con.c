#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define MAX 6

pthread_mutex_t mutex;
pthread_cond_t full;    //队列是否已满
pthread_cond_t empty;   //队列是否已空
int head,tail;

void *producer(void *arg)
{
    int i;
    for(i = 0; i < MAX * 3; i++)
    {
        pthread_mutex_lock(&mutex);

        while((tail + 1) % MAX == head)
        {
            printf("仓库已满！producer waiting\n");
            pthread_cond_wait(&full, &mutex);     //等待消费者消费
        }

        tail = (tail + 1) % MAX;
        printf("tail = %d\n",tail);
        pthread_cond_signal(&empty);        //发送队列未空消息
    
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    int i;
    for(i = 0; i < MAX * 3; i++)
    {
        pthread_mutex_lock(&mutex);
        
        while(tail % MAX == head)
        {
            printf("仓库已空！consumer waiting\n");
            pthread_cond_wait(&empty, &mutex);    //等待生产者生产
        }

        head = (head + 1) % MAX;
        printf("head = %d\n",head);
        pthread_cond_signal(&full);                 //发送队列未满消息

        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t pro,con;
    int statu1,statu2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    pthread_join(pro, (void *) &statu1);
    pthread_join(con, (void *) &statu2);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    
    return 0;
}
