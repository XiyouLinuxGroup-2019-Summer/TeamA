#include<iostream>
#include<bits/stdc++.h>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define ll long long 
#define db double

using namespace std;

/*
//J
bool cmp(const pair<int,int>& a, const pair<int,int>& b)
{
    return a.second < b.second;
}

int main()
{
    int n;
    pair<int,int> t[101];
    while(~scanf("%d",&n) && n != 0)
    {
        for(int i = 0; i < n; i++)
            cin >> t[i].first >> t[i].second;
        sort(t, t + n, cmp);

        int sum = 1;
        int m = t[0].second;
        for(int i = 1; i < n; i++)
        {
            if(t[i].first >= m)
            {
                sum++;
                m = t[i].second;
            }
        }
        cout << sum << endl;
    }
    return 0;
}
*/



/*
//H
typedef struct _data
{
    int a;
    int b;
}data;
data x[1001];

bool cmp(const data &n, const data &m)
{
    if(n.b == m.b)
        return n.a < m.a;
    return n.b > m.b;
}
int main()
{
    int t,n;
    int a[1001];
    cin >> t;
    while(t--)
    {
        memset(&a, 0, sizeof(a));
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> x[i].a;
        for(int i = 0; i < n; i++)
            cin >> x[i].b;
        sort(x, x + n, cmp);

        int sum = 0;
        for(int i = 0; i < n; i++)
        {
            int p = x[i].a;
            int flag = 0;
            while(p--)
            {
                if(a[p] == 0)
                {
                    a[p] = 1;
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
                sum += x[i].b;
        }
        cout << sum << endl;
    }
    return 0;
}
*/



/*
//G
typedef struct _data
{
    db a,b;
    db c;
}data;
data x[1001];

bool cmp(const data &a, const data &b)
{
    return a.c > b.c;
}

int main()
{
    int m,n;
    while(~scanf("%d %d",&m,&n) && (m != -1 || n != -1))
    {
        db sum = 0;
        int flag = 0;
        for(int i = 0; i < n; i++)
        {
            cin >> x[i].a >> x[i].b;
            x[i].c = x[i].a / x[i].b;
        }
        sort(x, x + n, cmp);
        for(int i = 0; i < n; i++)
        {
            if(flag >= m)
                break;
            else
            {
                if(x[i].b <= (m - flag))
                {
                    sum += x[i].a;
                    flag += x[i].b;
                }
                else
                {
                    sum += x[i].c * (m - flag);
                    flag = m;
                }

            }
        }
    printf("%.3lf\n",sum);
    }
    return 0;
}
*/



/*
//F
int main()
{
    int k;
    cin >> k;
    if(k > 36)
        cout << -1 << endl;
    else
    {
        if(k % 2 == 0)
        {
            int m = k / 2;
            while(m--)
                cout << 8;
            cout << endl;
        }
        else
        {
            int m = --k / 2;
            while(m--)
                cout << 8;
            cout << 6 << endl;
        }
    }
    return 0;
}
*/



/*
//E
int a[101];
int main()
{
    int n,m;
    int sum = 0;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    sort(a,a + n);
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] < 0 && j < m)
        {
            sum -= a[i];
            j++;
        }
        else
            break;
    }

    cout << sum << endl;
    return 0;
}
*/



/*
//D
int main()
{
    int n,a,b,c,t;
    int x[1001];
    cin >> n >> a >> b >> c >> t;
    for(int i = 0; i < n; i++)
        cin >> x[i];
    
    int sum = n * a;
    if(b >= c)
        cout << sum << endl;
    else
    {
        for(int i = 0; i < n; i++)
            sum += (t - x[i]) * (c - b);
        cout << sum << endl;
    }
    return 0;
}
*/



/*
//C
int main()
{
    int n,d;
    int x = 0;
    int m = 0;
    string a;
    scanf("%d %d",&n,&d);
    for(int i = 0; i < d; i++)
    {
        cin >> a;
        int sum = 0;
        for(int j = 0; j < n; j++)
        {
            if(a[j] == '0')
            {
                sum++;
                break;
            }
        }
        if(sum != 0)
            x++;
        else 
            x = 0;
        m = max(x,m);
    }
    cout << m << endl;
    return 0;
}
*/



/*
//B
//找规律...
int main()
{
    ll n;
    cin >> n;
    if(n == 1 || n == 2)
        cout << n << endl;
    else
    {
        if(n % 2 != 0)
            n--;
        cout << n / 2 + 1 << endl;
    }
    return 0;
}
*/



/*
//A
int main()
{
    int n,m;
    double a,b;
    while(~(scanf("%d %d",&n,&m)))
    {
        double c = 99999999;
        double x;
        for(int i = 0; i < n; i++)
        {
            scanf("%lf %lf",&a,&b);
            x = a / b;
            if(x < c)
                c = x;
        }
        printf("%.8lf\n",c * m);
    }
    return 0;
}
*/
