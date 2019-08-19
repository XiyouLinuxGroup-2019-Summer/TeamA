#include "server.h"

void showgroups(pack *recv)
{
    MYSQL_RES *res, *res1;   
    MYSQL_ROW row, row1;

    if (mysql_real_query(&mysql, "select * from group_info", (unsigned long)strlen("select * from group_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    strcpy(recv->message, "");
    while ( (row = mysql_fetch_row(res)) ) {
        if ( strcmp(row[1], recv->send_name)==0 ) {
            strcat(recv->message, row[0]);
            strcat(recv->message, ":\n");
            if (mysql_real_query(&mysql, "select * from group_info", (unsigned long)strlen("select * from group_info"))) {  
                printf("mysql_real_query select failure!\n"); 
                exit(0);  
            }
            res1 = mysql_store_result(&mysql);
            if (NULL == res) {  
                printf("mysql_store_result failure!\n");  
                exit(0);  
            }
            while ( (row1 = mysql_fetch_row(res1))) {
                if ( strcmp(row1[0], row[0])==0 && strcmp(row1[1], row[1])!=0 ) {
                    strcat(recv->message, row1[1]);
                    if ( search(head, row1[1]) != 0 ) {
                        strcat(recv->message, " online\n");
                    }
                    else 
                        strcat(recv->message, " downline\n");
                }
            }
        }
    }
    
    mysql_free_result(res);
    mysql_free_result(res1);
    send(recv->send_fd, recv, sizeof(pack), 0);
}
