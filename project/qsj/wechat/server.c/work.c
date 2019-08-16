
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
        break;
    case 3:
        deletefriend(p);
        break;
    case 4:
        showfriends(p);
        break;
    case 5:
        chatone(p);
        break;
    case 6:
        creategroup(p);
        break;
    case 7:
        inviteperson(p);
        break;
    case 8:
        addgroup(p);
        break;
    case 9:
        chatgroup(p);
        break;
    case 10:
        sendfile(p);
        break;
    default:
        break;
    }
}
