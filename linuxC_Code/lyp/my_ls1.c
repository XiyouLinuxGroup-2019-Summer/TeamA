#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<unistd.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define PARAM_NONE 0    //无参数
#define PARAM_A 1       //-a：显示所有文件
#define PARAM_L 2       //-l：显示文件的详细信息
#define PARAM_R 4       //-R：连同子目录内容一起列出来
#define MAXROWLEN 100   //一行显示的最多字符串

int g_leave_len = MAXROWLEN;    //一行剩余长度，用于输出对亲
int g_maxlen;                   //存放某目录下最长文件名的长度

int flag_param = PARAM_NONE;    //参数种类
int Index[256];                 //记录filenames下标
char PATH[PATH_MAX + 1];        //记录路径名（-R）

void display_dir(char *path);

//错误处理函数
void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line: %d",line);
    perror(err_string);
    exit(1);
}

//-l
void display_l(char *name)
{
    struct stat buf;
    char buf_time[32];
    struct passwd *psd;     //获取用户名
    struct group *grp;      //获取所属组名

    if(lstat(name,&buf) == -1)
        my_err("lstat",__LINE__);

    //获取并打印文件类型
    if(S_ISLNK(buf.st_mode))
        printf("1");
    else if(S_ISREG(buf.st_mode))
        printf("-");
    else if(S_ISDIR(buf.st_mode))
        printf("d");
    else if(S_ISCHR(buf.st_mode))
        printf("c");
    else if(S_ISBLK(buf.st_mode))
        printf("b");
    else if(S_ISFIFO(buf.st_mode))
        printf("f");
    else if(S_ISSOCK(buf.st_mode))
        printf("s");

    //获取并打印文件所有者权限
    if(buf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    //获取并打印同组其他用户对该文件的操作权限
    if(buf.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    //获取并打印其他用户对该文件操作权限
    if(buf.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");

    printf(" ");

    //根据uid和gid获取文件所有者的用户名和组名
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%3ld ",buf.st_nlink);    //打印文件链接数
    printf("%-9s",psd->pw_name);
    printf("%-8s",grp->gr_name);

    printf("%6ld",buf.st_size);      //打印文件大小
    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time) - 1] = '\0';  //去掉换行符
    printf(" %s",buf_time);         //打印文件时间信息
    printf(" %-s\n",name);          //打印文件名
}

void display_R_l(char *name)
{
    struct stat buf;
    if(lstat(name,&buf) == -1)
        my_err("lstat",__LINE__);


    if(S_ISDIR(buf.st_mode))
    {
        printf("\n");

        display_dir(name);
        
        char *p = PATH;
        while(*++p);
        while(*--p != '/');
        *p = '\0';
        chdir("..");
    }
}
//无-l，打印文件名（上下对亲）
void display_single(char *name)
{
    int i,len;

    //如果本行不足以打印一个文件名则换行
    if(g_leave_len < g_maxlen)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }

    len = strlen(name);
    len = g_maxlen - len;
    printf("%-s",name);

    for(i = 0; i < len; i++)
        printf(" ");
    printf("  ");   //多打两个空格
    g_leave_len -= (g_maxlen + 2);
}

void display_R_single(char *name)
{
    struct stat buf;
    if(lstat(name,&buf) == -1)
        my_err("lstat",__LINE__);

    if(S_ISDIR(buf.st_mode))
    {
        printf("\n\n");

        //g_maxlen = MAXROWLEN;

        display_dir(name);
        
        char *p = PATH;
        while(*++p);
        while(*--p != '/');
        *p = '\0';
        chdir("..");
    }
}

void display(char pathname[][PATH_MAX + 1], int count)
{
    int i,j;
    char name[256][PATH_MAX+1];

    //从路径中解析出文件名
    for(j = 0; j < count; j++)
    {
        for(i = 0; i < strlen(pathname[Index[j]]); i++)
        {
            name[j][i] = pathname[Index[j]][i];
        }
        name[j][i] = '\0';
    }

    switch(flag_param)
    {
    case PARAM_NONE:     
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_single(name[i]);
        break;
    
    case PARAM_A:           //-a
        for(i = 0; i < count; i++)
            display_single(name[i]);
        break;
    
    case PARAM_L:           //-l
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_l(name[i]);
        break;
    
    case PARAM_R:
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_single(name[i]);
        
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_R_single(name[i]);

        break;

    case PARAM_A + PARAM_L: //-a + -l
        for(i = 0; i < count; i++)
            display_l(name[i]);
        break;

    case PARAM_A + PARAM_R:
        for(i = 0; i < count; i++)
                display_single(name[i]);
        
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_R_single(name[i]);
        
        break;
    case PARAM_R + PARAM_L:
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_l(name[i]);
        
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_R_l(name[i]);

        break;
    case PARAM_A + PARAM_L + PARAM_R:
        for(i = 0; i < count; i++)
                display_l(name[i]);
        
        for(i = 0; i < count; i++)
            if(name[i][0] != '.')
                display_R_l(name[i]);

        break;
    default:
        break;
    }
}

//对文件名排序
void quickSort(char array[][PATH_MAX + 1], int left, int right)
{
    int i,j,t;
    char temp[PATH_MAX+1];
    i = left;
    j = right;
    strcpy(temp,array[Index[right]]);

    if(left > right)
        return;
    while(i != j)
    {
        while((strcmp(array[Index[i]],temp) <= 0) && i < j)
            i++;
        while((strcmp(array[Index[j]],temp) >= 0) && i < j)
            j--;
        if(i < j)
        {
            t = Index[i];
            Index[i] = Index[j];
            Index[j] = t;
        }
    }
    
    t = Index[right];
    Index[right] = Index[j];
    Index[j] = t;
    quickSort(array,left,j - 1);
    quickSort(array,j + 1,right);
}

void display_dir(char *path)
{
    DIR *dir;
    struct dirent *ptr;
    int count = 0;      //该目录下文件总数
    char filenames[256][PATH_MAX + 1];
    int i,j,len;

    if((flag_param & PARAM_R) != 0)
    {
        int len = strlen(PATH);
        if(len > 0)
        {
            if(PATH[len - 1] == '/')
                PATH[len - 1] = '\0';
        }
        if(path[0] == '.' || path[0] == '/')
            strcat(PATH,path);
        else
        {
            strcat(PATH,"/");
            strcat(PATH,path);
        }
        printf("%s:\n",PATH);
    }

    //获取该目录下文件总数和最长文件名
    dir = opendir(path);
    if(dir == NULL)
        my_err("opendir",__LINE__);
    while((ptr = readdir(dir)) != NULL)
    {
        if(g_maxlen < strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);

    if(count > 256)
        my_err("too many dir",__LINE__);

    /*
    //动态分配空间，减少栈的消耗
    char **filenames = (char **)malloc(sizeof(char *) * count);
    for(i = 0; i < count; i++)
        filenames[i] = (char *)malloc(sizeof(char) * PATH_MAX + 1);
    */

    //获取该目录下所有文件名
    dir = opendir(path);
    len = strlen(path);
    for(i = 0; i < count; i++)
    {
        ptr = readdir(dir);
        if(ptr == NULL)
            my_err("readdir",__LINE__);
        strcpy(filenames[i],ptr->d_name);

        Index[i] = i;
    }
    closedir(dir);

    //对文件名排序
    quickSort(filenames,0,count - 1);

    if(chdir(path) < 0)
        my_err("chdir",__LINE__);

    display(filenames,count);

    if((flag_param & PARAM_L) == 0)
        printf("\n");

}

int main(int argc, char *argv[])
{
    int i,j,k,n;
    char path[PATH_MAX+1];  //记录路径名（目录或文件名）
    char param[32];         //保存命令行参数（a，l...）
    struct stat buf;

    //命令行参数解析
    j = 0;
    n = 0;  //记录‘-’的出现次数
    for(i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            for(k = 1; k < strlen(argv[i]); k++, j++)
                param[j] = argv[i][k];  //获取‘-’后的参数保存到数组param中

            n++;
        }
    }

    //支持参数a和l，如果含有其他参数就报错
    for(i = 0; i < j; i++)
    {
        if(param[i] == 'a')
        {  
            flag_param |= PARAM_A;
            continue;
        }
        else if(param[i] == 'l')
        {
            flag_param |= PARAM_L;
            continue;
        }
        else if(param[i] == 'R')
        {
            flag_param |= PARAM_R;
            continue;
        }
        else
        {
            printf("my_ls: error -%c\n",param[i]);
            exit(1);
        }
    }
    param[j] = '\0';

    //如果没有输入文件名或目录，显示当前目录
    if((n + 1) == argc)
    {
        strcpy(path,".");
        display_dir(path);
        return 0;
    }

    i = 1;
    do
    {
        //如果不是目标文件名或目录，解析下一个命令行参数
        if(argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else
            strcpy(path,argv[i]);

        //如果目标文件或目录不存在，报错并退出程序
        if(lstat(path,&buf) == -1)
            my_err("lstat",__LINE__);

        if(S_ISDIR(buf.st_mode))    //argv[i]是目录
        {
            display_dir(path);
            i++;
        }
        else        //argv[i]是文件
        {
            display(path,1);
            printf("\n");
            i++;
        }
    }while(i < argc);

    
    return 0;
}
