#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

#define MAX_THREAD_NUM 6

typedef struct work
{
    void *(* process)(void *arg);   //任务函数指针
    void *arg;  //参数
    struct work *next;
}Work;

//线程池结构
typedef struct threadpoll
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    pthread_t *pthreadid;
    Work *tasks;    //任务队列
    int flag;       //标识线程池状态
    int max_thread_num; //线程池中允许的最大活动线程
    int cur_task;   //任务队列当前任务数
}Pool;

void pool_init();       //初始化线程池
int pool_add(void *(* process)(void *arg), void *arg); //添加任务
void *run(void *arg);   //工作线程
int pool_destroy();    //销毁线程池

Pool *pool = NULL;
void pool_init()
{
    pool = (Pool *)malloc(sizeof(Pool));

    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->cond), NULL);

    //初始化任务队列
    pool->tasks = NULL;

    pool->pthreadid = (pthread_t *)malloc(sizeof(pthread_t) * MAX_THREAD_NUM);
    pool->flag = 0;
    pool->max_thread_num = MAX_THREAD_NUM;
    pool->cur_task = 0;

    int i = 0;
    for(i = 0; i < MAX_THREAD_NUM; i++)
        pthread_create(&(pool->pthreadid[i]), NULL, run, NULL);
}

int pool_add(void *(* process)(void *arg), void *arg)
{
    //创建一个新任务
    Work *new_work = (Work *)malloc(sizeof(Work));
    new_work->process = process;
    new_work->arg = arg;
    new_work->next = NULL;

    //加锁
    pthread_mutex_lock(&(pool->mutex));

    //将任务添加到任务队列末尾
    Work *temp = pool->tasks;
    if(temp)
    {
        while(temp->next)
            temp = temp->next;
        temp->next = new_work;
    }
    else
        pool->tasks = new_work;
    pool->cur_task++;

    //唤醒线程去执行此任务,如果线程都在忙碌，这句就没有作用
    pthread_cond_signal(&(pool->cond));
    pthread_mutex_unlock(&(pool->mutex));
    
    return 0;
}

void *run(void *arg)
{
    printf("start thread %ld\n",pthread_self());
    while(!pool->flag)
    {
        pthread_mutex_lock(&(pool->mutex));

        //若等待队列为0则处于阻塞状态
        while(pool->cur_task == 0 && !pool->flag)
        {
            printf("thread %ld is waiting\n",pthread_self());
            pthread_cond_wait(&(pool->cond), &(pool->mutex));
        }
    

        //销毁线程池
        if(pool->flag)
        {
            pthread_mutex_unlock(&(pool->mutex));
            printf("thread %ld will exit\n",pthread_self());
            pthread_exit(NULL);
        }

        printf("thread %ld is starting to work\n",pthread_self());

        //等待队列长度-1，取出任务
        pool->cur_task--;
        Work *temp = pool->tasks;
        pool->tasks = pool->tasks->next;
        pthread_mutex_unlock(&(pool->mutex));

        //执行任务
        (*(temp->process))(temp->arg);
        free(temp);
        temp = NULL;    
    }
}

int pool_destroy()
{
    if(pool->flag)
        return -1;
    pool->flag = 1;

    //唤醒所有线程
    pthread_cond_broadcast(&(pool->cond));
    
    //等待所有线程结束
    int i = 0; 
    for(i = 0; i < pool->max_thread_num; i++)
        pthread_join(pool->pthreadid[i], NULL);
    free(pool->pthreadid);

    //销毁等待队列
    Work *temp = NULL;
    while(pool->tasks)
    {
        temp = pool->tasks;
        pool->tasks = pool->tasks->next;
        free(temp);
    }

    //销毁互斥锁与条件变量
    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->cond));

    free(pool);
    pool = NULL;
    
    return 0;
}

void *process(void *arg)
{
    printf("thread %ld is working on task %d\n",pthread_self(), *(int *)arg);
    sleep(1);
    return NULL;
}

int main()
{
    pool_init();

    sleep(2);

    //连续投入10个任务
    int *work_num = (int *)malloc(sizeof(int) * 10);
    int i = 0;
    for(i = 0; i < 10; i++)
    {
        work_num[i] = i;
        pool_add(process, &work_num[i]);
    }

    sleep(5);

    //销毁线程池
    pool_destroy();

    free(work_num);
    work_num = NULL;

    return 0;
}
