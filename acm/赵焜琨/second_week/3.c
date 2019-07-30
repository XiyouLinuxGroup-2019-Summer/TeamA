#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int n,d;
    scanf("%d%d",&n,&d);
    char a[101];
    int i,j;
    int len;
    int max = 0,t = 0,c = 0;
    for(i=0;i<d;i++)
    {
        c = 0;
        scanf("%s",a);
        len = strlen(a);
        for(j=0;j<len;j++)
        {
            if(a[j] == '1')
                c += 1;
        }
        if(c != len)
            t += 1;
        if(t > max)
            max = t;
        if(c == len)
            t = 0;
    }
    printf("%d\n",max);
}
