#include <stdio.h>
#include <mysql.h>
#include <string.h>

int main()
{
    MYSQL mysql;
    int rc;
    int i;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    int rows,fields;
    char *str = NULL;

    if(mysql_init(&mysql) == NULL)
    {
        printf("%s\n",mysql_error(&mysql));
        return -1;
    }

    if(mysql_real_connect(&mysql,NULL,"root","chu0326","yiyi",0,NULL,0)==NULL)
    {
        printf("%s\n",mysql_error(&mysql));
        return -1;
    }

    printf("连接服务器成功!\n");

/************************************* 添加信息 *****************************************/
  /*  str = "insert into student values ('00007','liu','wom','16','computer','120')";
    rc = mysql_real_query(&mysql,str,strlen(str));
    if(rc != 0)
    {
        printf("%s\n",mysql_error(&mysql));
        return -1;
    }
    else
        printf("添加成功!\n");
    */


/************************************ 删除信息 ******************************************/
  /*  str = "delete from student where name='zhao'";
    printf("%s\n",str);
    rc = mysql_real_query(&mysql,str,strlen(str));
    if(rc != 0)
    {
        printf("%s\n",mysql_error(&mysql));
       // return -1;
    }
    else
        printf("删除成功!\n");
    */


/***************************************** 查询信息 **************************************/
   str = "select * from student";
   rc = mysql_real_query(&mysql,str,strlen(str));
   if(rc != 0)
   {
        printf("%s\n",mysql_error(&mysql));
        return -1;
   }

   res = mysql_store_result(&mysql);
   if(res == NULL)
   {
        printf("%s\n",mysql_error(&mysql));
        return -1;
   }

    rows = mysql_num_rows(res); //查询结果行数
    fields = mysql_num_fields(res); //查询结果列数
    
    while( (row = mysql_fetch_row(res)))
    {
        for(i=0;i<fields;i++)
        {
            printf("%s\t",row[i]);
        }
        printf("\n");
    }


    mysql_free_result(res);
    mysql_close(&mysql);
    return 0;
}
