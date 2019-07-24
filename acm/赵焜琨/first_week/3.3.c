#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int i,j;
    int a[n];
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    
    int num = n;
    int flag = 2;
    int q = 0;
    int tmp = 0;
    for(i=0;i<n;i++)
    {   
        tmp = 0;
        for(j=0;j<n;j++)
        {
            if(flag > a[j])
            {
                num--;
                a[j] = 99999999;
                tmp = 1;
            }
        }
        if(tmp ==1)
            num++;
        //printf("%d\n",num);
        flag++;
        q++;
    }
    printf("%d\n",num);
}
