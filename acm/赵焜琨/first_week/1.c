#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    long long aa[1000];
    int i;
    for(i=0;i<n;i++)
    {
        scanf("%lld",&aa[i]);
    }

    int j;
    int num = 0;
    int flag = 0;
    for(j=0;j<i;j++) //j个数
    {   
        flag = 0;
        num = 0;
        while(aa[j] > 1 && flag == 0)
        {
            if(aa[j]%5 == 0)
            {
                aa[j] = (aa[j]*4)/5;
                num++;   
            }
            if(aa[j]%3 == 0)
            {
                aa[j] = (aa[j]*2)/3;
                num++;
            }
            if(aa[j]%2 == 0)
            {
                aa[j] = aa[j]/2;
                num++;
            }
            if(aa[j]%5 != 0 && aa[j]%3 != 0 && aa[j]%2 != 0)
            {
                flag = 1;
            }
        }
        if(aa[j] == 1)
            printf("%d\n",num);
        else
            printf("-1\n");
    }
    return 0;
}
