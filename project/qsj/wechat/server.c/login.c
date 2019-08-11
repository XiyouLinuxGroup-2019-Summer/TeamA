#include "server.h"

void login(pack *recv)
{
    char flag[5] = "";
    char s[256], str[256];
    MYSQL_RES *res;   
    MYSQL_ROW row;
    
    if (mysql_real_query(&mysql, "select * from nam_pass", (unsigned long)strlen("select * from nam_pass"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }  
    res = mysql_store_result(&mysql);  
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }  
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(recv->send_name, row[0]) == 0 ) { 
            flag[0] = '0';
            break;
        }
    }
    if ( flag[0] == '0' ) {
        Md5(recv->message, s);
        if ( strcmp(s, row[1]) == 0 ) { 
            if (search(head,recv->send_name) == 1) {
                flag[0] = '2';
                send(recv->send_fd, &flag, sizeof(flag), 0);
                mysql_free_result(res);
                return ;
            }
            else
                flag[0] = '3';
        }
        else {
            flag[0] = '1';
            send(recv->send_fd, &flag, sizeof(flag), 0);
            mysql_free_result(res);
            return ;
        }
    }

    else {
        flag[0] = '0';
        send(recv->send_fd, &flag, sizeof(flag), 0);
        mysql_free_result(res);
        return ;
    }

    add(&head, recv->send_fd, recv->send_name);
    send(recv->send_fd, &flag, sizeof(flag), 0);
    mysql_free_result(res);
}
