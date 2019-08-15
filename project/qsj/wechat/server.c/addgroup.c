#include "server.h"


void addgroup(pack *recv)
{
    int flag = 0;
    char str[256], name[256];
    MYSQL_RES *res;   
    MYSQL_ROW row;

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
            if ( strcmp(row[0], recv->recv_name)==0 && strcmp(row[1], recv->send_name)==0 ) {
                flag = 2;
                break;
            }
        }
        mysql_free_result(res);
        if ( flag == 2 ) {
            strcpy(recv->message, "this people is already in the group!");
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
            if ( strcmp(row[0], recv->recv_name)==0 && atoi(row[2]) == 1 ) {
                strcpy(name, row[1]);
                printf("%s", name);
                break;
            }
        }
        mysql_free_result(res);
        recv->recv_fd = search(head,name);
        recv->ans = 3;
        strcpy(recv->login_name, name);
        
        if ( recv->recv_fd != 0  ) {
            send(recv->recv_fd, recv, sizeof(pack), 0);
        }
        else {
            memcpy((void *)&send_array[num_send_pack++],(void *)recv, sizeof(pack));
        }
    }

    else if ( recv->ans == 2 ) {
        if ( recv->message[0] == '0' ) {
            sprintf(str,"insert into group_info values ('%s','%s', %d)",recv->recv_name,recv->send_name, 3);
            if (mysql_real_query(&mysql,str,strlen(str))) {
                printf("mysql_real_query insert failure!\n");
                exit(0);
            }
            strcpy(recv->message, "add group success");
        }
        else 
            strcpy(recv->message, "the group owner refused to let you join the group");
        
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

