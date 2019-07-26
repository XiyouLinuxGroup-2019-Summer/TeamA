#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

int qt(int x,int* array,int len) //a+b == -(c+d)
{ 
    int left,right,middle;
    left = 1,right = len;
    int i;
    //for(i=0;i<len;i++)
      //  printf("%d######\n",array[i]);
    while(left <= right)
    {
        middle = (left+right)/2;
        //printf("%d *** %d========>%d\n",middle,array[middle-1],x);
        if((-1)*array[middle-1]+x == 0)
        {
            return 1;
        }
        if((-1)*array[middle-1]+x > 0)
        {
            left = middle+1;
        }
        if((-1)*array[middle-1]+x < 0)
        {
            right = middle-1;
        }
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    int i,j;
    int a[n][4],b[4][n];
    for(i=0;i<n;i++)
    {
        for(j=0;j<4;j++)
        {
            scanf("%d",&a[i][j]);
            b[j][i] = a[i][j];
        }
    }

    int len_t = n *n;
    int c[len_t],d[len_t];
    int t = 0,q = 0;
    for(i=0;i<n;i++) //a+b->c[] ,c+d->d[]
    {
        for(j=0;j<n;j++)
        {
                c[t++] = b[0][i] + b[1][j];
                d[q++] = b[2][i] + b[3][j];
        }
    }
    //std::sort(c,c+len_t);
    std::sort(d,d+len_t);
    //for(i=0;i<len_t;i++)
      //  printf("%d****\n",d[i]);
    int flag = 0,flag_t;
    for(i=0;i<len_t;i++) //c[]里n个数
    {
        printf("c[]****%d\n",c[i]);
        flag_t = qt(c[i],d,len_t);
        printf("%d\n",flag_t);
        flag += flag_t;
    }
    printf("%d\n",flag);
}
