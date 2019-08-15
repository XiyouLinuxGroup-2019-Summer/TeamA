#include "client.h"

void addgroup()
{
    pack send_t;

    printf("please enter the groupname:\n");
    scanf("%s", send_t.recv_name);
    strcpy(send_t.send_name, username);
    send_t.type = 8;
    send_t.ans = 1;
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void add_group( pack pack_t )
{
    char choice_t[101];
    int choice;
    if ( pack_t.ans == 3 ) {
        printf("the person named %s want to join group\n", pack_t.send_name);
        printf("please enter your choice:\n");
        printf("1:agree\n");
        printf("2:refuse\n");
        scanf("%s", choice_t);
        choice = get_choice(choice_t);
        while ( 1 ) {
            if ( choice  == 1 ) {
                strcpy(pack_t.message, "0");
                break;
            }
            else if ( choice == 2 ) {
                strcpy(pack_t.message, "1");
                break;
            }
            else {
                printf("please enter the correct option\n");
                scanf("%s", choice_t);
                choice = get_choice(choice_t);
            }
        }
        pack_t.ans = 2;
        send(conn_fd, &pack_t, sizeof(pack), 0);
    }

    else
        printf("%s\n", pack_t.message);
}
