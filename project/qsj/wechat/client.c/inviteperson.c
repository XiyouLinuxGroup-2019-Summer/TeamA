#include "client.h"

void inviteperson()
{
    pack send_t;

    printf("please enter the group name:\n");
    scanf("%s", send_t.recv_name);
    send_t.ans = 3;
    send_t.type = 7;
    while ( 1 ) {
        memset(send_t.send_name, 0, sizeof(send_t.send_name));
        printf("please enter the membername:\n");
        scanf("%s", send_t.send_name);
        if (strcmp(send_t.send_name, "quit") == 0)
            break;
        send(conn_fd, &send_t, sizeof(pack), 0);
        sleep(1);
    }

}
