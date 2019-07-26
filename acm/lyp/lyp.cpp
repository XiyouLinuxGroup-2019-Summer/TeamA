#include<iostream>
//#include<bits/stdc++.h>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <algorithm>

#define ll long long 

using namespace std;

int main()
{

    return 0;
}








/*
//J
int main()
{
    int n;
    int i;
    int a[200010];
    char c[200010];

    while(~(scanf("%d",&n)))
    {
        memset(&a,0,sizeof(a));
        memset(c,0,sizeof(c));
        int sum = 0;

        for(i = 0; i < n; i++)
            scanf("%d",&a[i]);
        
        int k = n - 1;
        int j = 0;
        int m = 0;  
        for(i = 0; i <= k; i++)
        {
            if((a[i] <= a[k] && a[i] > m) || (a[i] > a[k] && a[k] < m && a[i] >= m)) 
            {
                sum++;
                c[j] = 'L';
                j++;
                //strcat(c,"L");
                m = a[i];
            }
            else if((a[i] > a[k] && a[k] > m) || (a[i] < a[k] && a[i] < m && a[k] > m))
            {
                sum++;
                c[j] = 'R';
                j++;
                //strcat(c,"R");
                m = a[k];
                k--;
                i--;
            }
            else
                break;
        }
        printf("%d\n%s\n",sum,c);
    }
    return 0;
}
*/



/*
//I
//用队列好像简单好多
int main()
{
    int n;
    int l,m;
    int i;
    int a[10000];
    char s[10000][10];
    char s1[2][10];

    cin >> n;
    while(n--)
    {
        cin >> l >> m;

        memset(&a,0,sizeof(a));
        memset(s,0,sizeof(s));
        
        l = l * 100;
        for(i = 0; i < m; i++)
            scanf("%d %s",&a[i],s[i]);

        int sum = 0,c = 0;
        memset(s1,0,sizeof(s1));
        strcpy(s1[0],"left");
        strcpy(s1[1],"right");
        
        for(i = 0; i < m; i++)
        {
            c = 0;
            if(a[i] == 0)
                continue;
            for(int j = i; j < m; j++)
            {
                if(strcmp(s1[0],s[j]) == 0)
                {
                    if(c + a[j] <= l)
                    {
                        c += a[j];
                        a[j] = 0;
                    }
                    else
                        break;
                }
            }
            sum++;
            swap(s1[0],s1[1]);
            i = -1;
        }
        cout << sum << endl;
    }
        return 0;
}
*/



/*
//H
//找规律
int main()
{
    ll n;
    while(~(scanf("%lld",&n)))
    {
        ll y = 1;
        ll x = 0;
        ll i;
        for(i = 1; i < n; i++)
        {
            x = y;
            y = x * 2;
            if(n >= x && n < y)
                break;
        }
        cout << i << endl;
    }
    return 0;
}
*/



/*
//G
//判断是否满足条件
ll func(ll v, ll n, ll k)
{
    ll sum = v;
    while(v)
    {
        sum += v / k;
        v /= k;
    }
    if(sum >= n)
        return 1;
    
    return 0;
}

//二分搜索
ll binary_search(int a, ll n, ll k)
{
    ll mid;
    ll c = n;
    while(a <= c)
    {
        mid = a + (c - a) / 2;  
        printf("%lld\n",mid);
        if(func(mid,n,k) == 1)
        {
            c  = mid - 1;
        }
        else 
            a = mid + 1;
    }
    return a;
}

int main()
{
    ll n,k;
    while(scanf("%lld %lld",&n,&k) != EOF)
    {
        ll v = binary_search(1,n,k);
        cout << v << endl;
    }
    return 0;
}
*/



/*
//F
char a[19][10] = {"pop","no","zip","zotz","tzec","xul","yoxkin","mol","chen","yax","zac","ceh","mac","kankin","muan","pax","koyab","cumhu"};
char b[20][10] = {"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau"};

int main()
{
    int n;
    cin >> n;
    cout << n << endl;
    while(n--)
    {
        int q,p;
        char s;
        char ss[10];
        int sum = 0;
        scanf("%d%c %s %d",&q,&s,ss,&p);

        sum = p * 365;
        for(int i = 0; i < 19; i++)
        {
            if(strcmp(ss,a[i]) == 0)
            {
                sum += i * 20;
                break;
            }
        }
        sum += q;

        p = sum / 260;
        q = sum % 260;
        
        int m = q % 20;
        
        int x = q % 13 + 1;

        printf("%d %s %d",x,b[m],p);
        cout << endl;
    }
    return 0;
}
*/



/*
//E
//巴什博弈
int main()
{
    int c,n,m;
    cin >> c;
    while(c--)
    {
        cin >> n >> m;
        if(n % (m + 1) == 0)
            cout << "second" << endl;
        else 
            cout << "first" << endl;
    }
    return 0;
}
*/



/*
//D
//刚开始输入的格式一直有问题...
char ch[26] = {'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
int main()
{
    string s;
    while(getline(cin,s))
    {
        if(s == "ENDOFINPUT") 
            break;
        else if(s == "START" || s == "END") 
            continue;

        for(int i = 0; i < s.size(); i++)
        {
            for(int j = 0; j < 26; j++)
            {
                if(ch[j] == s[i])
                {
                    if(j - 5 < 0)
                        s[i] = ch[j - 5 + 26];
                    else
                        s[i] = ch[j - 5];
                    break;
                }
            }
        }
    
        for(int i = 0; i < s.size(); i++)
            printf("%c",s[i]);
        cout << endl;
    }
    return 0;
}
*/




/*
//C
//用vector好像慢好多，应该直接用数组能快点
int main()
{
    ll n,m;
    while(cin >> n)
    {
        if(n < 1 || n > 2*100000)
            exit(1);

        vector<ll> a;
        for(int i = 0; i < n; i++)
        {
            cin >> m;
            a.push_back(m);
        }
        sort(a.begin(),a.end());
        
        int sum = 1;
        vector<ll>::iterator it;
        for(it = a.begin(); it != a.end(); it++)
        {
               if(*it >= sum)
                    sum++;
               else
                   continue;
        }
        cout << sum - 1 << endl;
    }        
        
}
*/



/*
//B
int main()
{
    ll t;
    cin >> t;
    while(t--)
    {
        ll a[3] = {0};
        ll n,m;
        cin >> n;
        while(n--)
        {
            cin >> m;
            if(m % 3 == 0)
                a[0]++;
            else if(m % 3 == 1)
                a[1]++;
            else if(m % 3 == 2)
                a[2]++;
        }
        a[0] += min(a[1],a[2]);
        a[0] += (max(a[1],a[2]) - min(a[1],a[2])) / 3;
        cout << a[0] << endl;
    }
    return 0;
}
*/
