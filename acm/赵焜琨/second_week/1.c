#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int i,j;
    double a[n][2];
    for(i=0;i<n;i++)
        scanf("%lf%lf",&a[i][0],&a[i][1]);

    double min = a[0][0]/a[0][1];
    double t;
    for(i=1;i<n;i++)
    {
        t = a[i][0]/a[i][1];
        if(t < min)
            min = t;
    }
    printf("%.8lf\n",min*m);
}
