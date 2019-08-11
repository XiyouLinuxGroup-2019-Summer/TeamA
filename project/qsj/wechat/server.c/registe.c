#include "server.h"

void registe(pack *recv)
{
    char flag[5] = "1";
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
        send(recv->send_fd, &flag, sizeof(flag), 0);
        mysql_free_result(res);
        return ;
    }
    Md5(recv->message, s);
    sprintf(str,"insert into nam_pass values ('%s','%s')",recv->send_name, s);
    if (mysql_real_query(&mysql,str,strlen(str))) {
        printf("mysql_real_query insert failure!\n");
        exit(0);
    }
    send(recv->send_fd, &flag, sizeof(flag), 0);
    mysql_free_result(res);
}
