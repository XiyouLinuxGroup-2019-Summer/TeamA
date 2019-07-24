#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);
    int i,j,len;
    int a[n][100]; //存储数据
    int t,k,tt=0;
    int num;
    for(i=0;i<n;i++) //n组数据
    {
        tt = 0;
        scanf("%d",&len);
        for(j=0;j<len;j++)
        {
            scanf("%d",&a[i][j]);
        }

        for(k=0;k<len-1;k++) //小到大 排序
        {
            for(j=k+1;j<len;j++)
            {
                if(a[i][k]>a[i][j])
                {
                    t = a[i][k];
                    a[i][k] = a[i][j];
                    a[i][j] = t;
                }
            }
        }
    
        k = 0;
        j = len - 1;
        while(k<j)
        {
            if(a[i][j] % 3 == 0)
                j--;
            if(a[i][k] % 3 == 0)
                k++;
            if(a[i][k]%3 != 0 && a[i][j]%3 !=0)
            {
                a[i][j] = a[i][j] + a[i][k];
                k++;
            }
        }
        for(k=0;k<len;k++)
        {
           // printf("%d\t",a[i][k]);
         if(a[i][k]%3 == 0)
            tt++;
        }
        printf("%d\n",tt);
    }
}
