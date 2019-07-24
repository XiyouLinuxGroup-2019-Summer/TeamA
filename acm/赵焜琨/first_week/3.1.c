#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    int i,j;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }

    int day = 1;
    int num = 0;
    int flag = 0;
    for(i=0;i<n;i++)
    {
        flag = 0;
        for(j=0;j<n;j++)
        {
            if(day == a[j])
            {
                num++;
                day++;
                break;
            }
            flag = 1;
        }
        if(flag == 1)
            day++;
    }

    printf("%d\n",num);
}
