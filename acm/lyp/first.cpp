#include<bits/stdc++.h>

using namespace std;

int main()
{

    return 0;
}



/*
//D
bool cmp(const int& a, const int& b)
{
    return a > b;
}

int a[12];
int main()
{
    int k;
    int sum = 0;
    int x = 0;
    cin >> k;
    for(int i = 0; i < 12; i++)
        cin >> a[i];
    if(k == 0)
    {
        cout << 0 << endl;
    }
    else
    {
        sort(a, a + 12, cmp);
        for(int i = 0; i < 12; i++)
        {
            sum += a[i];
            x++;
            if(sum >= k)
                break;
        }
        if(sum >= k)
            cout << x << endl;
        else
            cout << -1 << endl;
    }
    return 0;
}
*/



/*
//C
int main()
{
    int n,m;
    int z,x,c;
    z = x = c = 0;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> m;
        if(m % 3 == 0)
            z++;
        else if(m % 3 == 1)
            x++;
        else if(m % 3 == 2)
            c++;
    }
    cout << z / 2 + min(x,c) << endl;
    return 0;
}
*/



/*
//B
int a[4];
int main()
{
    int n,m;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> m;
        a[m]++;
    }
    sort(a + 1, a + 4);
    cout << n - a[3] << endl;
    return 0;
}
*/



/*
//A
bool cmp(const int& a, const int& b)
{
    return a > b;
}

int a[101];
int main()
{
    int n,m;
    int sum = 0;
    cin >> n;
    cin >> m;
    int i;
    for(i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n, cmp);
    for(i = 0; i < n; i++)
    {
        sum += a[i];
        if(sum >= m)
            break;
    }
    cout << i + 1 << endl;
    return 0;
}
*/
