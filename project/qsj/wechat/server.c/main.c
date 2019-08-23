#include "server.h"

int main()
{
    //signal(SIGINT, SIG_IGN);
    int optval, epfd, nfds, i, n;
    socklen_t len;
    struct sockaddr_in cli_addr, serv_addr;
    struct epoll_event ev, events[1000];
    pack recv_t, *p;
    pthread_t thid;

    mysql_init_t();
    epfd = epoll_create(10000);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock_fd < 0 ) {
        my_err("socket", __LINE__);
    }
    optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(int));
    ev.data.fd = sock_fd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd, &ev);
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0) {
        my_err("bind", __LINE__);
    }
    if (listen(sock_fd, 20) < 0) {
        my_err("listen", __LINE__);
    }
    len = sizeof(struct sockaddr_in);
    while (1) {
        nfds = epoll_wait(epfd,events,10000,1000);
        for ( i = 0; i < nfds; i++ ) {
            if ( events[i].data.fd == sock_fd ) {
                conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &len);
                printf("accept a new client\n");
                ev.data.fd = conn_fd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, conn_fd, &ev);
        
            }

            else if ( events[i].events & EPOLLIN ) {
                bzero(&recv_t, sizeof(pack));
                n = recv(events[i].data.fd,&recv_t,sizeof(pack), MSG_WAITALL) ;
                if(n < 0)
                {
                        close(events[i].data.fd);
                        my_err("recv", __LINE__);
                        continue;
                }
                else if(n == 0)
                {   
                    delet(&head, events[i].data.fd);
                    printf("客户端已关闭\n");
                    ev.data.fd = events[i].data.fd;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                    close(events[i].data.fd);
                    continue;
                }
                recv_t.send_fd = events[i].data.fd; 
                p = (pack*)malloc(sizeof(pack));
                memcpy(p, &recv_t, sizeof(pack));
                work((void *)p);

                /* if ( pthread_create(&thid, NULL, work, (void *)p) != 0 ) { */
                /*     my_err("pthread_create", __LINE__); */
                /*     exit(1); */
                /* } */

            }
        }

    }
    mysql_close(&mysql);
    fre(head);
    return 0;
}
