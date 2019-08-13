#include "client.h"

void chatone()
{
    pack send_t;
    int n;
    strcpy(send_t.send_name, username);
    printf("please enter the porson's name which you want to chat with:\n");
    scanf("%s", send_t.recv_name);getchar();
    while ( strcmp(send_t.send_name, send_t.recv_name) == 0 ) {
        printf("you shouldn't chat with yourself, please enter again\n");
        scanf("%s", send_t.recv_name);
    }
    printf("please enter the message you want to send:\n");
    fgets(send_t.message, sizeof(send_t.message), stdin);
    n = strlen(send_t.message);
    send_t.message[n-1] = '\0';

    send_t.type = 5;
    send(conn_fd, &send_t, sizeof(pack), 0);
}

void chat_one( pack pack_t )
{
    char choice_t[101];
    int choice, n;
    pack send_message;

    printf("the person named %s send message for you:\n", pack_t.send_name);
    printf("%s\n", pack_t.message);
    strcpy(send_message.recv_name, pack_t.send_name);
    strcpy(send_message.send_name, pack_t.recv_name);
    send_message.type = 5;
    do {
        deal_message_pack();
        chat();
        scanf("%s", choice_t);getchar();
        choice = get_choice(choice_t);
        switch ( choice ) {
        case 1:
            memset(send_message.message,0,strlen(send_message.message));
            printf("please enter the message:\n");
            fgets(send_message.message, sizeof(send_message.message), stdin);
            n = strlen(send_message.message);
            send_message.message[n-1] = '\0';
            send(conn_fd, &send_message, sizeof(pack), 0);
            memcpy((void *)&recv_message[num_message_pack++],(void *)&pack_t, sizeof(pack));
            break;
        default:
            break;
        }
    }while ( choice != 0 );
}

void chat()
{
    printf("*****0.exit        *****\n");
    printf("*****1.send message*****\n");
    printf("please enter your choice:\n");
}

void deal_message_pack ()
{
    int i;
    for ( i = 0; i < num_message_pack; i++ ) {
        printf("the person named %s send message for you:\n", recv_message[i].send_name);
        printf("%s\n", recv_message[i].message);
    }
    num_message_pack = 0;
}
