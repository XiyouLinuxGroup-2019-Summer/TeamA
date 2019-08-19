#include "client.h"

void *recv_pack( void *fd )
{
    int sockfd = *(int *)fd;
    pack pack_t;
    while ( 1 ) {
        if(recv(sockfd,&pack_t,sizeof(pack),0) <= 0) 
            my_err("recv",__LINE__);
       
        if ( pack_t.type == 3 )
            delete_friend(pack_t);
        if ( pack_t.type == 4 )
            show_friends(pack_t);
        if ( pack_t.type == 2 ) {
            memcpy((void *)&recv_array[num_recv_pack++],(void *)&pack_t, sizeof(pack));
            sleep(1);
            printf("you have a new friend request!\n");
        }
        if ( pack_t.type == 5 ) {
            if (strcmp(chatname, pack_t.send_name) == 0) 
                printf("%s\n", pack_t.message);
            else if (strcmp(username, pack_t.send_name) == 0)
                printf("%s\n", pack_t.message);
            else {    
                memcpy((void *)&recv_array[num_recv_pack++],(void *)&pack_t, sizeof(pack));
                sleep(1);
                printf("you have a new contact message!\n");
            }
        }
        if ( pack_t.type == 6 )
            printf("%s\n", pack_t.message);
        if ( pack_t.type == 7 )
            printf("%s\n", pack_t.message);
        if ( pack_t.type == 8 ) {
            memcpy((void *)&recv_array[num_recv_pack++],(void *)&pack_t, sizeof(pack));
            sleep(1);
            printf("you have a new group request!\n");
        }
        if ( pack_t.type == 9 ) {
            if (strcmp(chatname, pack_t.recv_name) == 0)
                printf("%s\n", pack_t.message);
            else {    
                memcpy((void *)&recv_array[num_recv_pack++],(void *)&pack_t, sizeof(pack));
                sleep(1);
                printf("you have a new group message!\n");
            }
        }
        if ( pack_t.type == 10 )
            send_file(pack_t);
        if ( pack_t.type == 11 )
            show_groups(pack_t);
        if ( pack_t.type == 12 )
            kick_person(pack_t);
        if ( pack_t.type == 13 )
            quit_group(pack_t);
    }
}

void deal_pack()
{
    int i, j;
    for ( i = 0; i < num_recv_pack; i++ ) {
        switch(recv_array[i].type) {
        case 2:
            add_friend(recv_array[i]);
            break;
        case 5:
            j = i;
            chat_one(recv_array[i], j);
            break;
        case 8:
            add_group(recv_array[i]);
            break;
        case 9:
            j = i;
            chat_group(recv_array[i], j);
            break;
        default:
            break;
        }
    }
    num_recv_pack = 0;
}

