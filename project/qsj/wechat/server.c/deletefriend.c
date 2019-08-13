#include "server.h"

void deletefriend(pack *recv)
{
    MYSQL_RES *res;   
    MYSQL_ROW row;
    int flag = 0;
    char str[256];

    if (mysql_real_query(&mysql, "select * from friend_ship", (unsigned long)strlen("select * from friend_ship"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(row[0], recv->send_name)==0 && strcmp(row[1], recv->recv_name) == 0 )
            flag = 1;
        else if ( strcmp(row[1], recv->send_name)==0 && strcmp(row[0], recv->recv_name) == 0 )
            flag = 1;
    }

    if ( flag == 1 ) {
        sprintf(str, "delete from friend_ship where name1 = '%s' and  name2 = '%s'", recv->send_name, recv->recv_name);
        mysql_real_query(&mysql,str,strlen(str));
        sprintf(str, "delete from friend_ship where name2 = '%s' and  name1 = '%s'", recv->send_name, recv->recv_name);
        mysql_real_query(&mysql,str,strlen(str));
        strcpy(recv->message, "delete friend success!");
        send(recv->send_fd, recv, sizeof(pack), 0);
    }
    
    else {
       sprintf(recv->message, "this person which named %s is not your friend!\n", recv->recv_name);
       send(recv->send_fd, recv, sizeof(pack), 0);
    }

    mysql_free_result(res);
}
