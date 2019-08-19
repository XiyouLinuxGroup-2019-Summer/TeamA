#include "client.h"

void kickperson()
{
    pack send_t;

    send_t.type = 12;
    printf("please enter the person's pet-name that you want to kick:\n");
    scanf("%s", send_t.send_name);
    while ( strcmp(send_t.send_name, username) == 0 ) {
        printf("you shouldn't kick yourself, please enter again\n");
        scanf("%s", send_t.send_name);
    }
    printf("please enter the group's name:\n");
    scanf("%s", send_t.recv_name);
    strcpy(send_t.message, username);
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void kick_person( pack pack_t )
{
    printf("%s\n", pack_t.message);
}
