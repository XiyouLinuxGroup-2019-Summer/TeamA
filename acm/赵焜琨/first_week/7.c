#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int t(int v,int k) //求k^p
{
    int p = 0;
    int t = 1;
    while(v/t > 0)
    {
        t = t*k;
        p++;
    }
    return t;
}

int main()
{
    int n,k,v;
    int i = 1,j;
    scanf("%d%d",&n,&k);
    if(n%2==0)
        j = n;
    else
        j = n-1;
    //printf("%d\n",j);
    int tt;
    while(1)
    {
        v = (i+j)/2 + 1;
        tt = t(v,k);
        printf("%d\t%d\n",v,tt);
        if(v/tt == 0 && v/(tt/k) >0)
            break;
        if(v/(tt/k) == 0)
            j = v;
        if(v/tt > 0)
        {
            i = v;
            printf("aaa");
            getchar();
        }
    }
    printf("%d\n",v);
}
