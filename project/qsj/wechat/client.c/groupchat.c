#include "client.h"

void chatgroup()
{
    pack send_t;
    char str[256];
    int n;
    time_t timep;

    strcpy(send_t.send_name, username);
    printf("please enter the group's name which you want to chat in:\n");
    scanf("%s", send_t.recv_name);getchar();
    strcpy(chatname, send_t.recv_name);
    send_t.type = 9;
    send_t.ans = 1;
    send(conn_fd, &send_t, sizeof(pack), 0);
    printf("********* CHAT IN %s *********\n", send_t.recv_name);
    while ( 1 ) {
        memset(send_t.message,0,strlen(send_t.message));
        fgets(send_t.message, sizeof(send_t.message), stdin);
        n = strlen(send_t.message);
        send_t.message[n-1] = '\0';
        time(&timep);
        send_t.ans = 2;
        if ( strcmp(send_t.message, "quit") == 0 ) {
            strcpy(chatname, "");
            break;
        }
        sprintf(str, "%s%s:\n%s", ctime(&timep), send_t.send_name, send_t.message);
        memset(send_t.message,0,strlen(send_t.message));
        strcpy(send_t.message, str);
        send(conn_fd, &send_t, sizeof(pack), 0);
    }
}

void chat_group( pack pack_t, int i )
{
    char str[256];
    int n, j;
    pack send_message;
    time_t timep;

    strcpy(send_message.send_name, pack_t.send_name);
    strcpy(send_message.recv_name, pack_t.recv_name);
    send_message.type = 9;

    strcpy(chatname, pack_t.recv_name);
    printf("********* CHAT IN %s *********\n", pack_t.recv_name);
    for ( j = i; j < num_recv_pack; j++ ) {
        if (strcmp(recv_array[j].recv_name, pack_t.recv_name) == 0 && recv_array[j].type == 9) {
            printf("%s\n", recv_array[j].message);
            memset(&recv_array[j], 0, sizeof(pack));
        }
    }
    while ( 1 ) {
        memset(send_message.message,0,strlen(send_message.message));
        fgets(send_message.message, sizeof(send_message.message), stdin);
        n = strlen(send_message.message);
        send_message.message[n-1] = '\0';
        time(&timep);
        if ( strcmp(send_message.message, "quit") == 0 ) {
            strcpy(chatname, "");
            break;
        }
        sprintf(str, "%s%s:\n%s", ctime(&timep), pack_t.send_name, send_message.message);
        memset(send_message.message,0,strlen(send_message.message));
        strcpy(send_message.message, str);
        send(conn_fd, &send_message, sizeof(pack), 0);
    }
}


