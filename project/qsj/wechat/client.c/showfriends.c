#include "client.h"

void showfriends()
{
    pack send_t;
    strcpy(send_t.send_name, username);
    send_t.type = 4;
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void show_friends( pack pack_t )
{
    printf("%s", pack_t.message);
}
