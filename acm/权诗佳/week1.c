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
