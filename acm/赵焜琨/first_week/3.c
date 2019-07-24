#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d",&n);

    int a[n];
    int i,j;
    int t;
    int day = 1;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    for(i=0;i<n;i++)
    {   
        printf("%d\t",a[i]);
        if(a[i]>=day)
        {
            day++;    
        }
    }
    printf("%d\n",day-1);
}
