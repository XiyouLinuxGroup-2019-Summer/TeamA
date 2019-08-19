#include "client.h"

void showgroups()
{
    pack send_t;
    strcpy(send_t.send_name, username);
    send_t.type = 11;
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void show_groups( pack pack_t )
{
    printf("%s", pack_t.message);
}
