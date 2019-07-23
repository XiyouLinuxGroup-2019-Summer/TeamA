#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
}node;


void add ( node**Head, int number );
void print ( node *Head );
void fre ( node *Head );
void reverse ( node **Head );

int main()
{
    int number;
    node *head = NULL;

    do {
        scanf("%d", &number);
        if ( number != -1 ) {
            add(&head, number);
        }
    }while( number != -1 );

    print(head);
    reverse(&head);
    print(head);
    fre(head);

}

void add ( node**Head, int number )
{
    node *p = (node*)malloc(sizeof(node));
    node *last = *Head;

    p->value = number;
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

void print ( node *Head )
{
    node *p = Head;
    while ( p ) {
        printf("%d\n", p->value);
        p = p->next;
    }
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

void reverse ( node **Head )
{
    node *pre = *Head, *cur, *rear, *p = *Head;

    if ( pre == NULL || pre->next == NULL )
        return ; 

    cur = pre->next;

    while ( cur ) {
        rear = cur->next;
        cur->next = pre;
        pre = cur;
        cur = rear;
    }
    p->next = NULL;
    *Head = pre;
}
