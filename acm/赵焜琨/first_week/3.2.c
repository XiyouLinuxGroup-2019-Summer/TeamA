#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    int i,j;
    int flag = 0;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        if(flag < a[i])
        {
            flag = a[i];
        }
    }
    //printf("%d\n",flag);
    int n_0 = 0;
    int num_0 = 0;
    int t = 0;
    while(n--)
    {
        for(i=0;i<n;i++)
        {
            a[i] -= 1;
            if(a[i] == 0)
            {
                n_0 += 1;
                break;
            }
        }
        if(n_0 > num_0)
        {
            t++;
            num_0 = n_0;
        }
    }
    printf("%d\n",t);
}
