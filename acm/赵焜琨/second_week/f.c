#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,t;
    scanf("%d",&n);

    if(n > 36)
        printf("-1\n");
    else
    {
        if(n%2 == 0)
        {
            t = n/2;
            while(t)
            {
                printf("8");
                t--;
            }
            printf("\n");
        }
        else if(n == 1)
            printf("4\n");
        else
        {
            t = n/2;
            while(t)
            {
                printf("8");
                t--;
            }
            printf("0\n");
        }
    }
}
