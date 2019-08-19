#include "server.h"

void quitgroup( pack *recv )
{
    int flag = 0;
    char str[256];
    MYSQL_RES *res;   
    MYSQL_ROW row;

    if (mysql_real_query(&mysql, "select * from group_info", (unsigned long)strlen("select * from group_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(row[0], recv->recv_name)==0  ) {
            flag = 3;
            break;
        }
    }
    mysql_free_result(res);
    if ( flag != 3 ) {
        strcpy(recv->message, "no this group!");
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;
    }
    if (mysql_real_query(&mysql, "select * from group_info", (unsigned long)strlen("select * from group_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(row[0], recv->recv_name)==0 && strcmp(row[1], recv->send_name) == 0 ) {
            flag = 2;
            recv->ans = atoi(row[2]);
            break;
        }
    }
    mysql_free_result(res);
    if ( flag != 2 ) {
        strcpy(recv->message, "you aren't in this group!");
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;
    }

    if (recv->ans == 1) {
        strcpy(recv->message, "you are the group owner,you shouldn't quit this group!");
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;
    }
    sprintf(str, "delete from group_info where groupname = '%s' and membername = '%s'", recv->recv_name, recv->send_name); 
    mysql_real_query(&mysql,str,strlen(str));
    strcpy(recv->message, "quit group success!");
    send(recv->send_fd, recv, sizeof(pack), 0);

}


