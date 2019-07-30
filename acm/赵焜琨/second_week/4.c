#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n,a,b,c,time;
    scanf("%d%d%d%d%d",&n,&a,&b,&c,&time);
    int aa[n];
    int i;
    int t;
    int sum = 0;
    for(i=0;i<n;i++)
        scanf("%d",&aa[i]);

    if(b >= c)
        printf("%d\n",n*a);
    else
    {
        t = c-b;//每次利润
        for(i=0;i<n;i++)
        {
            sum += (time - aa[i]);
        }
        printf("%d\n",t*sum+n*a);
    }
}
