#include "server.h"

void chatone(pack *recv)
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
        if ( strcmp(recv->recv_name, row[0]) == 0 ) {
            flag = 1;
            break;
        }
    }

    if ( flag != 1 ) {
        sprintf(recv->message, "no this person which named %s!", recv->recv_name);
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;
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
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(row[0], recv->send_name)==0 && strcmp(row[1], recv->recv_name) == 0 )
            flag = 2;
        else if ( strcmp(row[1], recv->send_name)==0 && strcmp(row[0], recv->recv_name) == 0 )
            flag = 2;
    }
    mysql_free_result(res);
    if ( flag != 2 ) {
        strcpy(recv->message, "this people isn't your friend!");
        send(recv->send_fd, recv, sizeof(pack), 0);
        return ;
    }

    recv->recv_fd = search(head, recv->recv_name);
    strcpy(recv->login_name, recv->recv_name);

    if ( recv->recv_fd != 0  ) {
        send(recv->recv_fd, recv, sizeof(pack), 0);
    }
    else {
        memcpy((void *)&send_array[num_send_pack++],(void *)recv, sizeof(pack));
    }

}
