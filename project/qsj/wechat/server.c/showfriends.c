#include "server.h"

void showfriends(pack *recv) 
{
    MYSQL_RES *res;   
    MYSQL_ROW row;
    int flag = 0;

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
            flag = 1;
            break;
        }
    }

    if ( flag == 0 ) {
        strcpy(recv->message, "no this user");
        send(recv->send_fd, recv, sizeof(pack), 0);
    }

    mysql_free_result(res);

    if (mysql_real_query(&mysql, "select * from friend_ship", (unsigned long)strlen("select * from friend_ship"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    strcpy(recv->message, "");
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(row[0], recv->send_name)==0 ) {
            strcat(recv->message, row[1]);
            if ( search(head,row[1]) != 0 )
                strcat(recv->message, "  online\n");
            else 
                strcat(recv->message, "  downline\n");
        }
        else if ( strcmp(row[1], recv->send_name)==0 ) {
            strcat(recv->message, row[0]);
            if ( search(head,row[0]) != 0 )
                strcat(recv->message, "  online\n");
            else 
                strcat(recv->message, "  downline\n");
        }
    }
    
    mysql_free_result(res);
    send(recv->send_fd, recv, sizeof(pack), 0);
}
