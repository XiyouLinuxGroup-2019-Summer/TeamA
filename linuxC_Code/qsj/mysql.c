#include <iostream>  
#include <mysql.h>
#include <string.h>
#pragma comment(lib, "libmysql.lib")  
using namespace std;
int main()
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // 初始化MYSQL变量
    mysql_init(&mysql);
    // 连接Mysql服务器，本例使用本机作为服务器。访问的数据库名称为"msyql"，参数中的user为你的登录用户名，***为登录密码，需要根据你的实际用户进行设置
    if (!mysql_real_connect(&mysql, "localhost", "root", "qsj122833", "qsj", 0, NULL, 0))
    {
        cout << "mysql_real_connect failure!" << endl;
        return 0;
    }
    // 查询mysql数据库中的user表
    if (mysql_real_query(&mysql, "select * from info", (unsigned long)strlen("select * from info")))
    {
        cout << "mysql_real_query failure!" << endl;
        return 0;
    }
    // 存储结果集
    res = mysql_store_result(&mysql);
    if (NULL == res)
    {
        cout << "mysql_store_result failure!" << endl;
        return 0;
    }
    // 重复读取行，并输出第一个字段的值，直到row为NULL
    while ((row = mysql_fetch_row(res)))
    {
        cout << row[0] << endl;
    }
    // 释放结果集
    mysql_free_result(res);
    // 关闭Mysql连接
    mysql_close(&mysql);

    return 0;
}
