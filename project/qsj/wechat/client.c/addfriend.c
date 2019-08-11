#include "client.h"

void addfriend()
{
    pack send_t;
    int n;
    strcpy(send_t.send_name, username);
    printf("please enter the person's pet-name you want to add:\n");
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

void add_friend( pack pack_t, int fd ) 
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
        if ( choice  == 1 ) 
            strcpy(pack_t.message, "0");
        else 
            strcpy(pack_t.message, "1");
        pack_t.ans = 2;
        send(fd, &pack_t, sizeof(pack), 0);
    }

    else
        printf("%s\n", pack_t.message);
}
