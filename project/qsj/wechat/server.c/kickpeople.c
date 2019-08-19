#include "server.h"

void kickperson(pack *recv)
{
    int flag = 0, status;
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
        strcpy(recv->message, "this person isn't in the group!");
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
        if ( strcmp(row[0], recv->recv_name)==0 && strcmp(row[1], recv->message) == 0 ) {
            status = atoi(row[2]);
            flag = 5;
            break;
        }
    }
    mysql_free_result(res);

    if ( flag != 5 ) {
        strcpy(recv->message, "you aren't in this group!");
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;

    }

    if ( recv->ans == 1 ) {
        strcpy(recv->message, "this person is group owner, you can't kick him");
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;
    }
    else if ( recv->ans == 2 ) {
        if ( status != 1 ) {
            strcpy(recv->message, "you don't have enough authority");  
            send(recv->send_fd, recv, sizeof(pack), 0);
            return ;
        }
    }
    else if ( recv->ans == 3 ) {
        if ( status == 3 ) {
            strcpy(recv->message, "you don't have enough authority");  
            send(recv->send_fd, recv, sizeof(pack), 0);
            return ;
        }
    }
    sprintf(str, "delete from group_info where groupname = '%s' and membername = '%s'", recv->recv_name, recv->send_name); 
    mysql_real_query(&mysql,str,strlen(str));
    strcpy(recv->message, "kick person success!");
    send(recv->send_fd, recv, sizeof(pack), 0);
}

