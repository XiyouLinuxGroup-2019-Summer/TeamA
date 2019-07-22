#include<iostream>
#include<bits/stdc++.h>

#define ll long long

using namespace std;

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
        
        int sum = 0;
        for(int i = 0,auto it = a.begin(); i < n,it != a.end(); i++,it++)
        {
            if(*it >= i)
                sum++;
        }
        cout << sum << endl;
    }
    return 0;
}





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
