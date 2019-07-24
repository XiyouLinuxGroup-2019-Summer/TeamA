#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
int main()
{
    int n;
    scanf("%d",&n);
    int i,j,t;
    int a[n];
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
 
 
    std::sort(a,a+n);
 
    int flag = 1;
    int count = 0;
    for(i=0;i<n;i++)
    {
        if(a[i]>flag || a[i]==flag)
        {
            flag++;
            count++;
        }
    }
    printf("%d\n",count);
}
