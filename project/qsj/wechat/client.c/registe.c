#include "client.h"

void registe()
{
    pack send_registe;
    char flag[5];
    char s1[256], s2[256];
    printf("please enter the pet-name you want to use:\n");
    scanf("%s",send_registe.send_name);
    printf("please enter the password you want to set:\n");
    scanf("%s", s1);
    printf("please enter your password again:\n");
    scanf("%s", s2);
    if ( strcmp(s1, s2) != 0 ) {
        printf("two inconsistent passwords!\n");
        return;
    }
    else 
        strcpy(send_registe.message, s1);
    send_registe.type = 0; 
    if( send(conn_fd, &send_registe, sizeof(pack), 0) < 0 )
        my_err("send", __LINE__);
    if ( recv(conn_fd, flag, sizeof(flag), 0) < 0 ) 
        my_err("recv", __LINE__);
    if ( flag[0] == '0' )
        printf("this prt-name had used,please change\n");
    else 
        printf("registe user success\n");
}


