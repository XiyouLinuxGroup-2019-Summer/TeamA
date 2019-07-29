#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    int i,j,k;
    int t,q;
    for(i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        int a[x],b[x];
        for(j=0;j<x;j++)
            scanf("%d",&a[j]);
        for(j=0;j<x;j++)
            scanf("%d",&b[j]);
     /*   for(j=0;j<x;j++)
        {
            printf("%d===%d\n",a[j],b[j]);
        }*/

        for(j=0;j<x-1;j++)
            for(k=j+1;k<x;k++)
            {
                if(a[j] < a[k])
                {
                    t = b[j];
                    b[j] = b[k];
                    b[k] = t;
                    q = a[j];
                    a[j] = a[k];
                    a[k] = q;
                }
            }

       /* for(j=0;j<x;j++)
        {
            printf("%d===%d\n",a[j],b[j]);
        }*/
        int sum = 0;
        int flag = 1;
        for(j=0;j<x;j++)
        {
            if(a[j] >= flag)
            {
                flag++;
                if(a[j] > max)
                {
                    max = a[j];
                }
                continue;
            }
        }
        printf("%d\n",sum);
    }
}
