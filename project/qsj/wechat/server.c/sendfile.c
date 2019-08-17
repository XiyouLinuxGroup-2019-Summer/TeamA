#include "server.h"

void sendfile(pack *recv)
{
    recv->recv_fd = search(head, recv->recv_name);
    send(recv->recv_fd, recv, sizeof(pack), 0);  
}
