#include "client.h"

void addfriend()
{
    pack send_t;
    int n;
    strcpy(send_t.send_name, username);
    printf("please enter the person's pet-name that you want to add:\n");
    scanf("%s", send_t.recv_name);getchar();
    while ( strcmp(send_t.send_name, send_t.recv_name) == 0 ) {
        printf("you shouldn't add yourself, please enter again\n");
        scanf("%s", send_t.recv_name);getchar();
    }
    printf("please enter the massage to show yourself:\n");
    fgets(send_t.message, sizeof(send_t.message), stdin);
    n = strlen(send_t.message);
    send_t.message[n-1] = '\0';
    send_t.type = 2;
    send_t.ans = 1;
    if ( send(conn_fd, &send_t, sizeof(pack), 0) < 0 )
        my_err("send", __LINE__);
}

void add_friend( pack pack_t ) 
{
    char choice_t[101];
    int choice;
    
    if ( pack_t.ans == 3 ) {
        printf("the person named %s want to be your friend,following is his message:\n", pack_t.send_name);
        printf("%s\n", pack_t.message);
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
