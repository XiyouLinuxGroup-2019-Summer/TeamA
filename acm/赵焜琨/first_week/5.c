#include <stdio.h>

int main()
{
    int x;
    scanf("%d",&x);
    int i,j;
    int n,m;
    for(i=0;i<x;i++)
    {
        scanf("%d%d",&n,&m);
        if(n%(m+1) == 0)
            printf("second\n");
        else
            printf("first\n");
    }
}
