#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

/* 如果5位哲学家都吃上饭了就退出 */

pthread_mutex_t chopstick[6];   //定义锁——1只筷子1个锁

typedef struct _data
{
    char phi;
    int flag;
}DATA;
DATA test[5];

//初始化
void fun()
{
    int i = 0;
    char ch = 'A';
    for(i = 0; i < 5; i++)
    {
        test[i].phi = ch + i;
        test[i].flag = 0;
    }
}

//初始化场景——每位哲学家左右为几号筷子
void get(int *left,int *right,char phi) 
{
    switch (phi)
    {
    case 'A':
        *left = 5;
        *right = 1;
        break;
    
    case 'B':
        *left = 1;
        *right = 2;
    break;

    case 'C':
        *left = 2;
        *right = 3;
        break;

    case 'D':
        *left = 3;
        *right = 4;
        break;

    case 'E':
        *left = 4;
        *right = 5;
    break;
    }
}

void *eat_think(void *arg)
{
    char phi = *(char *)arg;    //那位哲学家
    int left,right;

    get(&left,&right,phi);

    int i = 0;

    for(;;)
    {
        usleep(10);     //将线程挂起，单位为毫秒
        
        pthread_mutex_lock(&chopstick[left]);   //将当前哲学家的左边筷子加🔓
        
        //判断5位哲学家是否都吃上饭
        int sum = 0;
        for(i = 0; i < 5; i++)
            if(test[i].flag >= 1)
                sum++;
        if(sum >= 5)
        {
            printf("\e[1;32m%c哲学家吃上饭啦!\e[0m\n",phi);
            break;
        }
        //pthread_mutex_lock(&chopstick[left]);   //将当前哲学家的左边筷子加🔓
        printf("Philosopher %c fetches chopstick %d\n", phi,left);  //当前哲学家拿到左边筷子
        
        //能吃上饭的前提为拿到两只筷子
        //尝试给当前哲学家右边筷子加🔓
        //如果右边筷子已经被加过🔓则符合if条件——>给左边筷子解🔓
        //如果右边筷子没有被加🔓则加🔓
        if(pthread_mutex_trylock(&chopstick[right]) == EBUSY)   
        {
            pthread_mutex_unlock(&chopstick[left]);
            continue;
        }
        
        printf("Philosopher %c fetches chopstick %d\n", phi,right); //当前哲学家拿到右边筷子
        printf("\e[1;34mPhilosopher %c is eating.\e[0m\n",phi);      //当前哲学家吃上饭了
        
        for(i = 0; i < 5; i++)
        {
            if(test[i].phi == phi)
            {
                if(test[i].flag == 1)
                    break;
                test[i].flag++;
            }
        }
     
        usleep(10);
        pthread_mutex_unlock(&chopstick[left]);         //给当前哲学家的左边筷子解🔓
        printf("Philosopher %c release chopstick %d\n", phi,left);  //当前哲学家放下了左边筷子
        pthread_mutex_unlock(&chopstick[right]);        //给当前哲学家爱的右边筷子解🔓
        printf("Philosopher %c release chopstick %d\n", phi,right); //当前哲学家放下了右边筷子
    }
}

int main()
{
    pthread_t A,B,C,D,E; //5个哲学家
    int i;

    fun();

    //初始化锁
    for (i = 0; i < 5; i++)
        pthread_mutex_init(&chopstick[i],NULL);
    
    //创建5个线程代表5个哲学家
    pthread_create(&A, NULL, eat_think, (void *)"A");
    pthread_create(&B, NULL, eat_think, (void *)"B");
    pthread_create(&C, NULL, eat_think, (void *)"C");
    pthread_create(&D, NULL, eat_think, (void *)"D");
    pthread_create(&E, NULL, eat_think, (void *)"E");
    
    //等待线程结束
    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);
    pthread_join(D, NULL);
    pthread_join(E, NULL);
    
    return 0;
}
