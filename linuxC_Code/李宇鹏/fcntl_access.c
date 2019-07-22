#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

//自定义错误处理函数
void my_err(const char * err_string, int line)
{
    fprintf(stderr,"line:%d\n",line);
    perror(err_string);
    exit(1);
}

int main()
{
    int fd;
    int ret;
    int access_mode;
    
    if((fd = open("test4",O_RDWR|O_CREAT|O_EXCL,S_IRWXU)) == -1)
        my_err("open",__LINE__);
    else
        printf("create file success\n");

    //设置文件打开方式
    if((ret = fcntl(fd,F_SETFL,O_APPEND)) < 0)
        my_err("fcntl",__LINE__);
    //printf("%d\n",ret);    
    
    //获取文件打开方式
    if((ret = fcntl(fd,F_GETFL,0)) < 0)
        my_err("fcntl",__LINE__);
    //printf("%d\n",ret);    

    access_mode = ret & O_ACCMODE;
    //printf("%d %d\n",O_ACCMODE,access_mode);

    if(access_mode == O_RDONLY)
        printf("test4 access_mode: read only");
    if(access_mode == O_WRONLY)
        printf("test4 access_mode: write only");
    if(access_mode == O_RDWR)
        printf("test4 access_mode: read + write");
    
    if(ret & O_APPEND)
        printf(", append");
    if(ret & O_SYNC)
        printf(", sync");
    if(ret & O_NONBLOCK)
        printf(", nonblock");

    printf("\n");

    //printf("%d %d %d %d %d %d %d %d %d\n",O_RDONLY,O_WRONLY,O_RDWR,O_APPEND,O_NONBLOCK,O_SYNC,ret & O_APPEND,ret & O_NONBLOCK,ret & O_SYNC);
    return 0;
}
