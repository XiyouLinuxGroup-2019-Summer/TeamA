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
void do_read(int epfd, int fd, char *buf)
{
    int nread;
    nread = read(fd, buf, sizeof(buf));
    if(nread == -1)
    {
        my_err("read", __LINE__);
        close(fd);
        del_event(epfd, fd, EPOLLIN);
    }
    else if(nread == 0)
    {
        fprintf(stderr, "客户端关闭(%d)\n", fd);
        close(fd);
        del_event(epfd, fd, EPOLLIN);
    }
    else
    {
        printf("接受到(%d)：%s", fd, buf);
        mod_event(epfd, fd, EPOLLOUT);  //由读改为写，下一次循环时发送
    }
    return;
}

//处理写请求
void do_write(int epfd, int fd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if(nwrite == -1)
    {
        my_err("write", __LINE__);
        close(fd);
        del_event(epfd, fd, EPOLLOUT);
    }
    else
        mod_event(epfd, fd, EPOLLIN);
    memset(buf,0,MAXSIZE);
    return;
}

//处理接受到的连接请求
void handle_accept(int epfd, int sock_fd)
{
    int conn_fd;
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &len);
    if(conn_fd < 0)
            my_err("accept",__LINE__);
    else
    {
        printf("Welcome: %d, Ip: %s\n",conn_fd, inet_ntoa(cli_addr.sin_addr));
        add_event(epfd, conn_fd, EPOLLIN);
    }
    return;
}

int main(int argc, char *argv[])
{
    int sock_fd;
    int optval;
    socklen_t len;
    struct sockaddr_in serv_addr;

    int epfd;   //epoll的文件描述符
    struct epoll_event events[MAX_EVENTS];  //存放从内核读取的事件
    int ret_event;  //epoll_wait()的返回值
    int fd;
    char buf[MAXSIZE];
    memset(buf,0,sizeof(buf));

    int i = 0;

    len = sizeof(struct sockaddr_in);
    
    //创建TCP套接字
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);

    //设置该套接字使之可以重新绑定端口
    optval = 1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
        my_err("setsockopt",__LINE__);

    //初始化服务器端地址结构
    memset(&serv_addr,0,len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //将套接字绑定到本地端口
    if(bind(sock_fd,(struct sockaddr *)&serv_addr,len) < 0)
        my_err("bind",__LINE__);

    //将套接字转化为监听套接字
    if(listen(sock_fd,LISTENQ) < 0)
        my_err("listen",__LINE__);

    //多路复用
    epfd = epoll_create(MAX_EVENTS);    //创建句柄
    add_event(epfd, sock_fd, EPOLLIN);    
    
    //获取已准备好的事件
    while(1)
    {
        ret_event = epoll_wait(epfd, events, MAX_EVENTS, -1);   //等待事件的到来
        //遍历需要处理的事件
        for(i = 0; i < ret_event; i++)
        {
            fd = events[i].data.fd; 
            //根据文件描述符类型和事件类型进行处理
            if((fd == sock_fd) && (events[i].events & EPOLLIN))
                handle_accept(epfd,sock_fd);
            else if(events[i].events & EPOLLIN)
                do_read(epfd,fd,buf);
            else if(events[i].events & EPOLLOUT)
                do_write(epfd,fd,buf);
        }
    }
    close(epfd);

    return 0;
}
