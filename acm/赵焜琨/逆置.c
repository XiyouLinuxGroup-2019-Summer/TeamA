#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student
{
    int num;
    struct student * next;
};
struct student *create()
{
    int t = 0;
    struct student *head;
    struct student *new,*old;
    new = old =(struct student *)malloc(sizeof(struct student));
    scanf("%d",&new->num);
    while(new->num != -1)
    {
        if(t == 0)
        {
            head = new;
            old = new;
            t++;
        }
        else
        {
            new->next = NULL;
            old->next = new;
            old = new;
        }
        new = (struct student *)malloc(sizeof(struct student));
        scanf("%d",&new->num);
    }
    free(new);
    return head;
}
void print(struct student *head)
{
    struct student *t = head;
    while(t != NULL)
    {
        printf("%d\t",t->num);
        t = t->next;
    }
}
struct student *nz(struct student *head)
{
    struct student *a,*b,*c;
    a = head;
    b = head->next;
    int t =1;
    c = head->next->next;
    while(c != NULL)
    {
        if(t == 1)
        {
            a->next = NULL;
            t++;
        }
        b->next = a;
        a = b;
        b = c;
        c = c->next;
    }
    b->next = a;
    return b;
}
int main()
{
    struct student *t,*q;
    t = create();
    print(t);
    printf("\n");
    q = nz(t);
    print(q);
    printf("\n");
}
