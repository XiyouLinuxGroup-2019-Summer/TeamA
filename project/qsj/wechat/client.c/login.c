#include "client.h"

int login()
{
    pack send_login;
    char flag[5] = "";
    printf("please enter your pet-name:\n");
    scanf("%s", send_login.send_name);
    strcpy(username, send_login.send_name);
    printf("please enter your password:\n");
    scanf("%s", send_login.message);
    send_login.type = 1;
    if( send(conn_fd, &send_login, sizeof(pack), 0) < 0 )
        my_err("send", __LINE__);
    if ( recv(conn_fd, flag, sizeof(flag), 0) < 0 ) 
        my_err("recv", __LINE__);
    if ( flag[0] == '0' )
        printf("no this user\n");
    else if ( flag[0] == '1' )
        printf("the password is error\n");
    else if ( flag[0] == '2' )
        printf("this user has logined\n");
    else {
        printf("login success\n");
        return 1;
    }
    return 0;
}


