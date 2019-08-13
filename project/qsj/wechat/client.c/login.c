#include "client.h"

int login()
{
    pack send_login;
    char flag[5] = "";
    char str[256];

    printf("please enter your pet-name:\n");
    scanf("%s", send_login.send_name);getchar();
    strcpy(username, send_login.send_name);
    printf("please enter your password:\n");
    strcpy(send_login.message, pas(str));
    send_login.type = 1;
    if( send(conn_fd, &send_login, sizeof(pack), 0) < 0 )
        my_err("send", __LINE__);
    if ( recv(conn_fd, flag, sizeof(flag), 0) < 0 ) 
        my_err("recv", __LINE__);
    printf("\n");
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

char *pas( char *s )
{
    char ch;
    int i = 0;

    strcpy(s, "");
    
    while ( 1 ) {
		ch = getch1();
        if ( ch == 13 )
            break;
        
        s[i] = ch;
        if ( s[i] == 127 ) {
            printf("\b \b");
            i = i-2;
            if ( i < 0 ) {
                i = 0;
                continue;
            }
        }
        else 
            printf("*");
        i++;
    }
    s[i] = '\0';
    return s;
}

int getch1(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;

     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }

     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }

     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
         return -1;
     }

     return ch;
}
