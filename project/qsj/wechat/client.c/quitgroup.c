#include "client.h"

void quitgroup()
{
    pack send_t;

    send_t.type = 13;
    printf("please enter the group's name which you want to quit:\n");
    scanf("%s", send_t.recv_name);
    strcpy(send_t.send_name, username);
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void quit_group( pack pack_t )
{
    printf("%s\n", pack_t.message);
}
