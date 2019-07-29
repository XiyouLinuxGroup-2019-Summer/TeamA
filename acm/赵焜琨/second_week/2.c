#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    int t = 1;
    int flag = 0,sum = 0,buf;
    while(t != n)
    {
        buf = n/t;
        printf("%d---\n",buf);
        if(buf != flag)
        {
            sum++;
            flag = buf;
        }
        t++;
    }
    printf("%d\n",sum);
}
