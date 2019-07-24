#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);

    int a[n][100]; //存储数据
    int i,j,k,l;
    int t = 0;
    int len;
    int temp;

    for(i=0;i<n;i++)
    {
        t = 0;
        scanf("%d",&len);
        for(j=0;j<len;j++)
        {
            scanf("%d",&a[i][j]);
        }
        
        for(j=0;j<len;j++)
        {   
            a[i][j] = a[i][j]%3;
            if(a[i][j] == 0)
            {
                t++;
            }
        }
        for(j=0;j<len;j++)
        {
            for(k=0;k<len;k++)
            {
                if( a[i][j]%3==1 && a[i][k]%3==2 )
                {
                    a[i][j] = 0;
                    a[i][k] = 0;
                    t++;
                }
            }
        }

        for(j=0;j<len-2;j++)
        {
            for(k=j+1;k<len-1;k++)
            {
                for(l=k+1;l<len;l++)
                {
                    if((a[i][j]+a[i][k]+a[i][l])%3 == 0 && a[i][j]!=0&&a[i][k]!=0&&a[i][l]!=0)
                    {
                        a[i][j] = 0;
                        a[i][k] = 0;
                        a[i][l] = 0;
                        t++;
                    }
                }
            }
        }
        printf("%d\n",t);
    }
}
