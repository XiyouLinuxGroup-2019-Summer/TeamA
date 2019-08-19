#include "client.h"

void creategroup()
{
    pack send_t;
    
    printf("please enter the group name:\n");
    scanf("%s", send_t.recv_name);
    strcpy(send_t.send_name, username);
    send_t.ans = 1;
    send_t.type = 6;
    send(conn_fd, &send_t, sizeof(pack), 0);
    sleep(1);
    while ( 1 ) {
        memset(send_t.send_name, 0, sizeof(send_t.send_name));
        printf("please enter the membername:\n");
        scanf("%s", send_t.send_name);
        if (strcmp(send_t.send_name, "quit") == 0)
            break;
        printf("please enter the status:(2 or 3)\n");
        scanf("%d", &send_t.ans);
        send(conn_fd, &send_t, sizeof(pack), 0);
        sleep(1);
    }
}

