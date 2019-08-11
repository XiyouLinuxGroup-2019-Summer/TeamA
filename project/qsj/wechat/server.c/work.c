
#include "server.h"

void *work( void *recv )
{
    pack *p = (pack *)recv;
    switch ( p->type ) {
    case 0:
        registe(p);
        break;
    case 1:
        login(p);
        break;
    case 2:
        addfriend(p); 
    default:
        break;
    }
}
