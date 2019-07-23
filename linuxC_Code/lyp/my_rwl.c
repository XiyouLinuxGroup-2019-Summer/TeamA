#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

//自定义读数据函数
int my_read(int fd)
{
    int len;
    int ret;
    int i;
    char read_buf[64];

    //获取文件长度并保持文件读写指针在文件开始处
    if(lseek(fd,0,SEEK_END) == -1)  //将指针移动到文件末尾
        my_err("lseek",__LINE__);
    if((len = lseek(fd,0,SEEK_CUR)) == -1)  //获取文件长度
        my_err("lseek",__LINE__);
    if(lseek(fd,0,SEEK_SET) == -1)  //将指针移动到文件开头
        my_err("lseek",__LINE__);
    
    printf("len(文件长度): %d\n",len);

    //读数据
    if((ret = read(fd,read_buf,len)) < 0)
        my_err("read",__LINE__);

    //打印数据
    for(i = 0; i < len; i++)
        printf("%c ",read_buf[i]);
    printf("\n");

    return ret;
}

int main()
{
    int fd;
    char write_buf[32] = {"hello world!"};
    
    if((fd = open("test3",O_RDWR|O_CREAT|O_EXCL,S_IRWXU)) == -1)
        my_err("open",__LINE__);
    else
        printf("create file success\n");
    
    //写数据
    if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf))
        my_err("write",__LINE__);

    printf("ret(read返回值):%d\n",my_read(fd));

    //演示文件间隔
    printf("/*-----------------------*/\n");
    if(lseek(fd,10,SEEK_END) == -1)
        my_err("lseek",__LINE__);
    if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf))
        my_err("write",__LINE__);
    printf("ret(read返回值):%d\n",my_read(fd));
    
    close(fd);
    return 0;
}
