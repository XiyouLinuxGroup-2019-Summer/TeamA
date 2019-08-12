#include<iostream>
#include<bits/stdc++.h>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

struct node
{
    int x;//横坐标
    int y;//纵坐标
    int xx;
    int yy;
};
int main()
{
    struct node que[25];
    int a[5][5] = {0},b[5][5] = {0};
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};//方向

    int head,tail;
    int star_x,star_y,p,q;
    int x,y,i,j,k;
    int c[25][2];

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
            scanf("%d",&a[i][j]);
    star_x = star_y = 0;
    p = q = 4;
    //队列初始化
    head = tail = 0;
    que[tail].x = star_x;
    que[tail].y = star_y;
    tail++;
    b[star_x][star_y] = 1;

    while(head < tail)
    {
        for(k = 0; k <= 3; k++)  //计算下个点坐标
        {
            x = que[head].x + next[k][0];
            y = que[head].y + next[k][1];
            if(x < 0 || x > 4 || y < 0 || y > 4)    //判断是否越界
                continue;
            if(a[x][y] == 0 && b[x][y] == 0)        //添加
            {
                b[x][y] = 1;
                que[tail].x = x;
                que[tail].y = y;
                que[tail].xx = que[head].x;
                que[tail].yy = que[head].y;
                tail++;
            }
            if(x == p && y == q)
                break;
        }
        head++;
        if(x == p && y == q)
            break;
    }
    k = 0;
    for(i = tail - 1; i > 0; i = j)
    {
        for(j = i - 1; j > 0; j--)
        {
            if(que[i].xx == que[j].x && que[i].yy == que[j].y)
            {
                c[k][0] = que[j].x;
                c[k][1] = que[j].y;
                k++;
                break;
            }
        }
    }
    cout << "(0, 0)" << endl;
    for(i = k - 1; i >= 0; i--)
        cout << "(" << c[i][0] << ", " << c[i][1] << ")" << endl;      
    cout << "(4, 4)" << endl;
    return 0;
}















/*
//A
int main()
{
    int a[4];
    for(int i = 0; i < 4; i++)
        cin >> a[i];

    sort(a, a + 4);
    if(a[0] + a[1] > a[2] || a[0] + a[1] > a[3] || a[0] + a[2] > a[3] || a[1] + a[2] > a[3])
        cout << "TRIANGLE" << endl;
    else if(a[0] + a[1] == a[2] || a[0] + a[1] == a[3] || a[0] + a[2] == a[3] || a[1] + a[2] == a[3])
        cout << "SEGMENT" << endl;
    else
        cout << "IMPOSSIBLE" << endl;
    return 0;
}
*/
