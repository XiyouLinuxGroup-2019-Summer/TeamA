#include "client.h"

void *recv_pack( void *fd )
{
    int sockfd = *(int *)fd;
    pack pack_t;
    while ( 1 ) {
        if(recv(sockfd,&pack_t,sizeof(pack),0) < 0)
            my_err("recv",__LINE__);
        
        switch( pack_t.type ) {
        case 2:
            add_friend(pack_t, sockfd);
            break;
        }
        
    }
}
