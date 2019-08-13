#include "client.h"

void *recv_pack( void *fd )
{
    int sockfd = *(int *)fd;
    pack pack_t;
    while ( 1 ) {
        if(recv(sockfd,&pack_t,sizeof(pack),0) < 0)
            my_err("recv",__LINE__);
       
        memcpy((void *)&recv_array[num_recv_pack++],(void *)&pack_t, sizeof(pack));
        
    }
}

void deal_pack()
{
    int i;
    for ( i = 0; i < num_recv_pack; i++ ) {
        switch(recv_array[i].type) {
        case 2:
            add_friend(recv_array[i]);
            break;
        case 3:
            delete_friend(recv_array[i]);
            break;
        case 4:
            show_friends(recv_array[i]);
            break;
        case 5:
            chat_one(recv_array[i]);
            break;
        default:
            break;
        }
    }
    num_recv_pack = 0;
}

