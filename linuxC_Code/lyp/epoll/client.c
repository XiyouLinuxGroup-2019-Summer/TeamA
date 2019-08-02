#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define PORT 9527
#define LISTENQ 10
#define MAXSIZE 1024
#define MAX_EVENTS 1000

//错误处理函数
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}
//添加事件
void add_event(int epfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    return;
}

//修改事件
void mod_event(int epfd, int fd, int state)
{ 
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
    return;
}

//删除事件
void del_event(int epfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
    return;
}

//处理读请求
void do_read(int epfd, int fd, int sock_fd, char *buf)
{
    int nread;
    nread = read(fd, buf, sizeof(buf));
    if(nread == -1)
    {
        my_err("read", __LINE__);
        close(fd);
    }
    else if(nread == 0)
    {
        fprintf(stderr, "服务器关闭\n");
        close(fd);
        close(epfd);
        exit(1);
    }
    else
    {
        if(fd == STDIN_FILENO)
            add_event(epfd, sock_fd, EPOLLOUT);
        else
        {
            del_event(epfd, sock_fd, EPOLLIN);
            add_event(epfd, STDOUT_FILENO, EPOLLOUT);
        }
    }
    return;
}

//处理写请求
void do_write(int epfd, int fd, int sock_fd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if(nwrite == -1)
    {
        my_err("write", __LINE__);
        close(fd);
    }
    else
    {
        if(fd == STDOUT_FILENO)
            del_event(epfd, fd, EPOLLOUT);
        else
            mod_event(epfd, fd, EPOLLIN);
    }
    memset(buf,0,MAXSIZE);
    return;
}


int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in serv_addr;

    int epfd;   //epoll的文件描述符
    struct epoll_event events[MAX_EVENTS];  //存放从内核读取的事件
    int ret_event;  //epoll_wait()的返回值
    int fd;
    char buf[MAXSIZE];
    memset(buf,0,sizeof(buf));
  
    int i = 0;

    //初始化服务器端地址
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    
    //创建TCP套接字
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);

    //向服务器端发送连接请求
    if(connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0)
        my_err("connect",__LINE__);
 
    //多路复用
    epfd = epoll_create(MAX_EVENTS);    //创建句柄
    add_event(epfd, STDIN_FILENO, EPOLLIN);    
    
    //获取已准备好的事件
    while(1)
    {
        ret_event = epoll_wait(epfd, events, MAX_EVENTS, -1);   //等待事件的到来
        //遍历需要处理的事件
        for(i = 0; i < ret_event; i++)
        {
            fd = events[i].data.fd; 
            //根据文件描述符类型和事件类型进行处理
            if(events[i].events & EPOLLIN)
                do_read(epfd, fd, sock_fd, buf);
            else if(events[i].events & EPOLLOUT)
                do_write(epfd, fd, sock_fd, buf);
        }
    }
    close(epfd);

    return 0;
}
