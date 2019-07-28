// A
#include<stdio.h>

int a, b, c;

int main()
{
    long long int  num;
    int n;
    
    scanf("%d", &n);

    while ( n-- ) {
        a = b = c = 0;
        scanf("%lld", &num);

        while ( num % 2 == 0 ) {
            num/=2;
            a+=1;
        }

        while ( num % 3 == 0 ) {
            num/=3;
            b+=2;
        }

        while ( num % 5 == 0 ) {
            num/=5;
            c+=3;
        }

        if ( num != 1 )
            printf("-1\n");
        else 
            printf("%d\n", a+b+c);
    }
    
    return 0;
}

//B
#include<stdio.h>

int a[1000];

int main()
{
    int n, t, i, num, b, c;
    
    scanf("%d", &n);

    while ( n-- ) {
        scanf("%d", &t);
        num = b = c = 0;

        for ( i = 0; i < t; i++ ) {
            scanf("%d", &a[i]);
        }

        for ( i = 0; i < t; i++ ) {
            if ( a[i] % 3 == 0 ) {
                num++;
                continue;
            }
            if ( a[i] % 3 == 1 ) {
                b++;
                continue;
            }
            if ( a[i] % 3 == 2 ) {
                c++;
                continue;
            }
        }
            
        if ( b > c ) {
            num+=c;
            t = (b-c)/3;
            num+=t;
        }
        else {
            num+=b;
            t = (c-b)/3;
            num+=t;
        }

        printf("%d\n",num);
        
    }

    return 0;
}

//C
#include <stdio.h>

int a[1000];

int main()
{
    int n, i, j, temp, ans = 0;

    scanf("%d", &n);
    
    for ( i = 0; i < n; i++ ) {
        scanf("%d", &a[i]);
    }

    for ( i = 0; i < n; i++ ) {
        for ( j = i; j < n-1; j++ ) {
            if ( a[j] > a[j+1] ) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    temp = 1;
    for ( i = 0; i < n; i++ ) {
        if ( a[i] >= temp ) { 
            temp++;
            ans++;   
        }
    }

    printf("%d\n", ans);
    return 0;
}

//D
#include <stdio.h>
#include <string.h>

char s[210], a[20];

int main ()
{
    int i, l;

    while ( gets(a) ) {
        if ( strcmp(a, "ENDOFINPUT") == 0 )
            break;
        if ( strcmp(a, "START") == 0 ) {
            gets(s);
            l = strlen(s);
            for ( i = 0; i < l; i++ ) {
                if ( s[i] >= 'A' && s[i] < 'F' ) {
                    s[i] = 86+(s[i]-'A');
                }
                else if( s[i] >= 'F' && s[i] <= 'z' ) {
                    s[i] = s[i]-5;
                }
            }
            printf("%s\n", s);
        }
    }

    return 0;
}

//E
#include <stdio.h>

int main ()
{
    int i, n, m;

    scanf("%d", &i);

    while ( i-- ) {
        scanf("%d %d", &n, &m);
        if ( n%(m+1) )
            printf("first\n");
        else 
            printf("second\n");
    }

    return 0;
}

//F
#include <stdio.h>
#include <string.h>

int main ()
{
    int n, i, day, year, sum;
    char s[10];
    char *s1[19] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
    char *s2[20] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};   
    
    scanf("%d", &n);
    printf("%d\n", n); 
    while ( n-- ) {
        scanf("%d. %s %d", &day, s, &year);

        for ( i = 0; i < 19; i++ ) {
            if ( strcmp(*(s1+i),s) == 0 )
                break;
        }

        sum = year*365+i*20+day+1;

        year = sum/260;
        day = sum%13;
        if ( day == 0 )
            day = 13;
        i = sum%20;
        if ( i == 0 )
            i = 20;
        if ( sum%260 == 0 ) {
            printf("%d %s %d\n", day, *(s2+i-1), year-1);
            continue;
        }
        printf("%d %s %d\n", day, *(s2+i-1), year);
    }

    return 0;
}
//G
#include <stdio.h>

int flag = 1;

int main ()
{
    int left = 1, right, mid, n, k, ans, m, sum;

    scanf ("%d %d", &n, &k);
    right = n;

    while ( left <= right && flag == 1 ) {
        if ( left == right )
            flag = 0;
        sum = 0;
        mid = (left+right)/2;
        m = 1;
        while (  mid/m > 0 ) {
            sum+=mid/m;
            m = m*k;
        }
    

        if ( sum >= n ) {
            right = mid-1;
            ans = mid;
        }

        else {
            left = mid+1;
        }
    }

    printf("%d\n", ans);

    return 0;
}
//H
#include <stdio.h>

int main()
{
    int n, i, sum, m;
    scanf("%d", &n);

    sum = 0;
    for ( i = 1; i <= n; i++ ) {
         m = i;
         sum = 1;
         while ( m ) {
             sum*=2;
             m--;
         }
         sum--;
        if ( sum >= n )
            break;
    }

    printf("%d\n", i);
    return 0;
}
//I
#include <stdio.h>
#define MAX 10000000
int a[MAX], b[MAX];

int main()
{
    int N, m, n, num, i, sum, l, r, L, R, flag;
    char s[6];
    scanf("%d", &N);

    while ( N-- ) {
        scanf("%d %d", &m, &n);
        m*=100;
        

        l = r = 0;
        for ( i = 0; i < n; i++ ) {
            scanf("%d %s", &num, s);
            if ( s[0] == 'l' ) {
                a[l++] = num;
            }
            else {
                b[r++] = num;
            }
        }

        flag = 1;
        i = L = R = 0;
        while ( i < l ) {
            sum = 0;
            while ( sum <= m ) {
                if ( a[i] == 0 ) {
                    flag = 0;
                    break;
                }
                sum+=a[i++];
            }
            i--;
            L++;
            if ( flag == 0 )
                break;
        }

        flag = 1;
        i = 0;
        while ( i < r ) {
            sum = 0;
            while ( sum <= m ) {
                if ( b[i] == 0 ) {
                    flag = 0;
                    break;
                }
                sum+=b[i++];
            }
            i--;
            R++;
            if ( flag == 0 )
                break;
        }
       
        sum = 0;
        if ( R >= L )
            sum = 2*R;
        else 
            sum = 2*L-1;
        printf("%d\n", sum);

    }

    return 0;
}
//J
#include <stdio.h>
#include <string.h>

char a[200100];

int main()
{
    int t, n, k, left, right, mid, i, l;

    scanf("%d", &t);
    while ( t-- ) {
        
        scanf("%d %d", &n, &k);
        scanf("%s", a);
        right = n;
        left = 1;

        while ( left < right ) {
            mid = (left+right)/2;
            i = l = 0;
            while ( a[i] == '0' ) {
                i++;
            }
            while ( i < n ) {
                if ( a[i] == '0' ) {
                    i++;
                    continue;
                }
                i+=mid;
                l++;
            }
            if ( l <= k ) {
                right = mid;
            }
            else
                left = mid+1;
        }
        
        printf("%d\n", left);

    }

    return 0;
}
//K
#include <stdio.h>

char a[200100], b[200100];

int main()
{
    int n, i, j, k;
    scanf("%d", &n);
    scanf("%s", a);

    i = k = 0;
    j = i+1;
    while ( j < n ) {
        if ( a[i] != a[j] ) {
            b[k++] = a[i];
            b[k++] = a[j];
            i = j+1;
            j = j+2;
        }
        else
            j++;
    }

    printf("%d\n%s\n", n-k, b);
    return 0;
}
//L
#include <stdio.h>
#include <string.h>

char a[200100];

int main()
{
    int t, n, k, left, right, mid, i, l;

    scanf("%d", &t);
    while ( t-- ) {
        
        scanf("%d %d", &n, &k);
        scanf("%s", a);
        right = n;
        left = 1;

        while ( left < right ) {
            mid = (left+right)/2;
            i = l = 0;
            while ( i < n ) {
                if ( a[i] == '0' ) {
                    i++;
                    continue;
                }
                i+=mid;
                l++;
            }
            if ( l <= k ) {
                right = mid;
            }
            else
                left = mid+1;
        }
        
        printf("%d\n", left);

    }

    return 0;
}
//N
#include <stdio.h>
#include <stdlib.h>

#define MAX 4100
int a[MAX], b[MAX], c[MAX], d[MAX],m[MAX*MAX], n[MAX*MAX];
 
int cmp ( const void *a , const void *b ) 
{ 
  return *(int *)a - *(int *)b; 
}

int up_down( int *num,  int l, int r, int key )
{
    int mid;

    while ( l < r ) {
        mid = (l+r)/2;
        if ( num[mid] + key >= 0 )
            r = mid;
        else
            l = mid+1;
    }
    if ( (num[l] + key) == 0 )
        return l;
    else
        return -1;
}

int main()
{
    int N, i, j, k, e, f, ans;
    scanf("%d", &N);

    for ( i = 0; i < N; i++ ) {
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
    }

    k = 0;
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < N; j++ ) {
            m[k] = a[i]+b[j];
            n[k++] = c[i]+d[j];
        }
    }

    qsort(m, k, sizeof(int), cmp);

    ans = 0;
    for ( i = 0; i < k; i++ ) {
        e = up_down(m,0,k-1,n[i]);
        if ( e != -1 ) {
            ans++;
            for ( f = e+1; f < k; f++ ) {
                if ( m[e] == m[f] )
                    ans++;
                else 
                    break;
            }
        }
    }
    
    printf("%d\n", ans);

}
