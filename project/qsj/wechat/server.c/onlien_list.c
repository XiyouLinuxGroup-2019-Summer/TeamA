#include "server.h"

void add ( node**Head, int fd_t, char *nam )
{
    node *p = (node*)malloc(sizeof(node));
    node *last = *Head;

    p->fd = fd_t;
    strcpy(p->name, nam);
    p->next = NULL;

    if ( last ) {
        while ( last->next ) {
            last = last->next;
        }
        last->next = p;
    }

    else {
        *Head = p;
    }
}

void delet ( node **Head, int fd_t )
{
    node *p = *Head, *q;

    for ( q = NULL ; p ; q = p, p = p->next ) {
        if ( p->fd == fd_t ) {
            if ( q ) {
                q->next = p->next;
            }
            else {
                *Head = p->next;
            }
            free(p);
            break;
        }
    }
}
    
int search( node *Head, char *nam )
{
    node *p = Head, *q;

    for ( q = NULL ; p ; q = p, p = p->next ) {
        if ( strcmp(p->name, nam) == 0 ) {
            return p->fd;
        }
    }

    return 0;
}


void fre ( node *Head )
{
    node *p = Head, *q;

    while ( p ) {
        q = p;
        p = p->next;
        free(q);
    }
}

