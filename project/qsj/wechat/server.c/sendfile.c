#include "server.h"

void sendfile(pack *recv)
{
    recv->recv_fd = search(head, recv->recv_name);
    send(recv->recv_fd, recv, sizeof(pack), MSG_WAITALL);  
}
<<<<<<< HEAD
=======

>>>>>>> df9f5e8c941a76df32cca99f112bc68a2c03cb9b
