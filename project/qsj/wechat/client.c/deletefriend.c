#include "client.h"

void deletefriend()
{
    pack send_t;
    strcpy(send_t.send_name, username);
    printf("please enter the person's pet-name that you want to delete:\n");
    scanf("%s", send_t.recv_name);
    while ( strcmp(send_t.send_name, send_t.recv_name) == 0 ) {
        printf("you shouldn't delete yourself, please enter again\n");
        scanf("%s", send_t.recv_name);
    }
    send_t.type = 3;
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void delete_friend ( pack pack_t )
{
    printf("%s\n", pack_t.message);
}
