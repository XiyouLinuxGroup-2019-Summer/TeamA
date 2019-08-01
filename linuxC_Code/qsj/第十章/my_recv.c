#define MY_RECV_C

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "my_recv.h"

void my_err(const char * err_string, int line)
{
    fprintf(stderr, "line:%d", line);
    perror(err_string);
    exit(1);
}

int my_recv(int conn_fd, char *data_buf, int line)
{
    static char recv_buf[BUFSIZE];
    static char *pread;
    static int len_remain = 0;
    int i;
    if ( len_remain <= 0 ) {
        if ( (len_remain = recv(conn_fd, recv_buf, sizeof(recv_buf), 0)) < 0 ) {
            my_err("recv", __LINE__);
        } else if ( len_remain == 0 ) {
            return 0;
        }
        pread = recv_buf;
    }

    for ( i = 0; *pread != '\n'; i++ ) {
        if ( i > line ) {
            return -1;
        }
        data_buf[i] = *pread++;
        len_remain--;
    }

    len_remain--;
    pread++;

    return i;
}


