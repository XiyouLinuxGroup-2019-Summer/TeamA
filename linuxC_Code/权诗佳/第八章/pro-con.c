#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
 
int g_count = 0;
 
pthread_mutex_t mutex;
pthread_cond_t cond;
 
void *consume(void *arg)
{
	while(1){
		pthread_mutex_lock(&mutex);
        while(g_count == 0){
            printf("consume is waiting: %lu\n", pthread_self());
            pthread_cond_wait(&cond, &mutex);
		}
        printf("consume is %lu, g_count is %d\n", pthread_self(), g_count);
        g_count--;
	    pthread_mutex_unlock(&mutex);	
        sleep(1);
	}
	pthread_exit(0);
}
 
void *produce(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
        if(g_count >= 10){
            printf("产品太多，休眠1秒\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);
            continue;
        }
        printf("start produce the product\n");
        g_count++;
        printf("produce is %lu, g_count is %d\n", pthread_self(), g_count);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
	pthread_exit(0);
}
 
int main()
{
	pthread_t tidCustom1, tidCustom2;
	pthread_t tidProduce1, tidProduce2, tidProduce3;
	
	pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    
	pthread_create(&tidCustom1, NULL, consume, NULL);
	pthread_create(&tidCustom1, NULL, consume, NULL);
 
	sleep(3);
 
	pthread_create(&tidProduce1, NULL, produce, NULL);
	pthread_create(&tidProduce2, NULL, produce, NULL);
	pthread_create(&tidProduce3, NULL, produce, NULL);
	
	
	pthread_join(tidCustom1, NULL);
	pthread_join(tidCustom2, NULL);

	pthread_join(tidProduce1, NULL);
	pthread_join(tidProduce2, NULL);
	pthread_join(tidProduce3, NULL);
	
    printf("parent exit\n");
	pthread_exit(0);
}

