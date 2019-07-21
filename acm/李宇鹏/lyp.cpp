#include<iostream>
#include<bits/stdc++.h>

#define ll long long

using namespace std;

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

