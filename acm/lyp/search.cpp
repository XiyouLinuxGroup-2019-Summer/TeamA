
#include<bits/stdc++.h>

using namespace std;

//简单dfs
int n,m;    //边界
int start_x,start_y,end_x,end_y;  //起点，终点
int x,y;    //坐标
int G[51][51];        //地图
int book[51][51];   //记录
int Min = 99999999;

//判断
bool judge(int x, int y)
{
    if(x < 1 || x > n || y < 1 || y > m || G[x][y] == 1)
        return false;
    return true;
}

void dfs(int tx, int ty, int step)
{
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};   //方向

    //出口
    if(tx == end_x && ty == end_y)
    {
        //要最短路径
        if(step < Min)
            Min = step;
        return;
    }

    //枚举4种走法（上下左右）
    for(int i = 0; i < 4; i++)
    {
        x = tx + next[i][0];
        y = ty + next[i][1];
        
        //判断是否满足条件
        if(judge(x, y) && !book[x][y])
        {
            book[x][y] = 1;         //标记该点已走过
            dfs(x, y, step + 1);    //尝试下一个点
            book[x][y] = 0;         //尝试结束，取消标记
        }
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> G[i][j];
    
    cin >> start_x >> start_y >> end_x >> end_y;
    book[start_x][start_y] = 1; //标记起点已在路径中
    dfs(start_x, start_y, 0);
    cout << Min << endl;
    return 0;
}



/*
//简单bfs
typedef struct _node
{
    int x;
    int y;
    int s;  //步数
}node;

int n,m;    //边界
int start_x,start_y,end_x,end_y;  //起点，终点
int x,y;    //坐标
int G[51][51];        //地图
int book[51][51];   //记录

//判断
bool judge(int x, int y)
{
    if(x < 1 || x > n || y < 1 || y > m || G[x][y] == 1)
        return false;
    return true;
}

void bfs(node start)
{
    queue<node> q;
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};   //方向
    
    //将起点入队
    q.push(start);
    //标记起点
    book[start_x][start_y] = 1;

    //队列不为空时循环
    while(!q.empty())
    {
        node now = q.front();
        q.pop();
        
        //出口
        if(now.x == end_x && now.y == end_y)
        {
            cout << now.s << endl;
            return;
        }

        //枚举4种走法（上下左右）
        for(int i = 0; i < 4; i++)
        {
            x = now.x + next[i][0];
            y = now.y + next[i][1];
            
            //判断是否满足条件
            if(judge(x,y) && !book[x][y])
            {
                node New;
                New.x = x;
                New.y = y;
                New.s = now.s + 1;
                book[x][y] = 1;     //标记，每个点只需入队一次，所以不需要还原
                q.push(New);        //入队
            }
        }
    }
    cout << "没有通路" << endl;
}
int main()
{
    node start;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> G[i][j];
    
    cin >> start_x >> start_y >> end_x >> end_y;
    
    start.x = start_x;
    start.y = start_y;
    start.s = 0;
    bfs(start);
    return 0;
}
*/
