#include "server.h"

void chatgroup(pack *recv)
{
    MYSQL_RES *res;   
    MYSQL_ROW row;
    int flag = 0;
    char name[256];

    strcpy(name, recv->send_name);
    if ( recv->ans == 1 ) {
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
            if ( strcmp(recv->recv_name, row[0]) == 0 ) {
                flag = 1;
                break;
            }
        }

        if ( flag != 1 ) {
            sprintf(recv->message, "no this group which named %s!", recv->recv_name);
            send(recv->send_fd, recv, sizeof(pack), 0);
            return ;
        }
        mysql_free_result(res);
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
        if ( strcmp(row[0], recv->recv_name)==0 && strcmp(row[1], name)!=0 ) {
            strcpy(recv->send_name, row[1]);
            recv->recv_fd = search(head, recv->send_name);
            strcpy(recv->login_name, recv->send_name);
            if ( recv->recv_fd != 0  ) {
                send(recv->recv_fd, recv, sizeof(pack), 0);
            }
            else {
                memcpy((void *)&send_array[num_send_pack++],(void *)recv, sizeof(pack));
            }
        }                
    }
    mysql_free_result(res);
}



