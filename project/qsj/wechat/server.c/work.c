
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
        break;
>>>>>>> df9f5e8c941a76df32cca99f112bc68a2c03cb9b
=======
        break;
    case 11:
        showgroups(p);
        break;
    case 12:
        kickperson(p);
        break;
    case 13:
        quitgroup(p);
        break;
>>>>>>> 86bc901a8348b09c58785771745bc406fdd32fa4
    default:
        break;
    }
}
