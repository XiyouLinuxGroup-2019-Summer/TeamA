#include "client.h"

int main()
{
    signal(SIGINT, SIG_IGN);
    pthread_t thid;
    conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( conn_fd < 0 ) 
        my_err("socket",__LINE__);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ( connect(conn_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0 )
        my_err("connect", __LINE__);
    if ( menu() == 0 ) {
        close(conn_fd);
        return 0;
    }

    if (pthread_create(&thid, NULL, recv_pack, (void *)&conn_fd) != 0) {                                                                   
        my_err("pthread_create", __LINE__);
        exit(1);
    }
    function();
    close(conn_fd);
    return 0;
}

