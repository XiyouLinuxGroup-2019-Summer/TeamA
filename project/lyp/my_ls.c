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

//初步实现-a,-l,-R,-r,-d,-f及相应结合操作

#define PARAM_NONE 0    //无参数
#define PARAM_A 1       //-a：显示所有文件
#define PARAM_L 2       //-l：显示文件的详细信息
#define PARAM_R 4       //-R：连同子目录内容一起列出来
#define PARAM_r 8       //-r：反向输出
#define PARAM_d 16      //-d：只显示目录本身信息
#define PARAM_f 32      //-f：无序输出
#define MAXROWLEN 100   //一行显示的最多字符串

int g_leave_len = MAXROWLEN;    //一行剩余长度，用于输出对亲
int g_maxlen;                   //存放某目录下最长文件名的长度

int flag_param = PARAM_NONE;    //参数种类
int Index[100000];        //记录filenames下标
char PATH[PATH_MAX + 1];        //记录路径名（-R）
int flag;

void display_dir(char *path);

//错误处理函数
void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line: %d ",line);
    perror(err_string);
    exit(1);
}

//染色函数
void color(char *name, struct stat buf)
{
    if(S_ISDIR(buf.st_mode))    //目录
        printf("\e[1;34m%-s\e[0m",name);
    else if(S_ISDIR(buf.st_mode) && (buf.st_mode & 0777) == 0777)   //满权限目录
        printf("\e[1;34;42m%-s\e[0m",name);
    else if(S_ISLNK(buf.st_mode))   //符号链接
        printf("\e[1;36m%-s\e[0m",name);
    else if(buf.st_mode & S_IXUSR || buf.st_mode & S_IXGRP || buf.st_mode & S_IXOTH)    //可执行文件
        printf("\e[1;32m%-s\e[0m",name);
    else
        printf("%-s",name);
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
    printf(" %s ",buf_time);         //打印文件时间信息
    color(name,buf);
    printf("\n");
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
        chdir("..");    //返回上层目录
    }
    free(name);
}
//无-l，打印文件名（上下对亲）
void display_single(char *name)
{
    int i,len;
    struct stat buf;
    if(lstat(name,&buf) == -1)
        my_err("lstat",__LINE__);

    //如果本行不足以打印一个文件名则换行
    if(g_leave_len < g_maxlen)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }

    len = strlen(name);
    len = g_maxlen - len;
    color(name,buf);

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
        
        display_dir(name);
        
        char *p = PATH;
        while(*++p);
        while(*--p != '/');
        *p = '\0';
        chdir("..");
        printf("\n");
    }
    free(name);
}

void display(char **name, int count)
{
    int i,j;
    int index[100000];
    memset(&index,0,sizeof(index));
    struct stat buf;

    //-r需要逆序
    if(flag_param & PARAM_r)
    {
        for(i = count - 1,j = 0; i >= 0; i--,j++)
            index[j] = Index[i];
    }
    else
    {
        for(i = 0; i < count; i++)
            index[i] = Index[i];
    }

    memset(&Index,0,sizeof(Index));

    switch(flag_param)
    {

    case PARAM_r + PARAM_f:
    case PARAM_f:
    case PARAM_r:
    case PARAM_NONE:     
        for(i = 0; i < count; i++)
            if(name[index[i]][0] != '.')
                display_single(name[index[i]]);
        break;
    
    case PARAM_A + PARAM_r + PARAM_f:
    case PARAM_A + PARAM_f:
    case PARAM_A + PARAM_r:
    case PARAM_A:           
        for(i = 0; i < count; i++)
            display_single(name[index[i]]);
        break;
    
    case PARAM_L + PARAM_r + PARAM_f:
    case PARAM_L + PARAM_f:
    case PARAM_L + PARAM_r:
    case PARAM_L:           
        for(i = 0; i < count; i++)
            if(name[index[i]][0] != '.')
                display_l(name[index[i]]);
        break;
    
    case PARAM_R + PARAM_r + PARAM_f:
    case PARAM_R + PARAM_f:
    case PARAM_R + PARAM_r:
    case PARAM_R:
        for(i = 0; i < count; i++)
            if(name[index[i]][0] != '.')
                display_single(name[index[i]]);
        
        for(i = 0; i < count; i++)
            if(name[index[i]][0] != '.')
                display_R_single(name[index[i]]);
        break;

    case PARAM_A + PARAM_L + PARAM_r + PARAM_f:
    case PARAM_A + PARAM_L + PARAM_f:
    case PARAM_A + PARAM_L + PARAM_r:
    case PARAM_A + PARAM_L:
        for(i = 0; i < count; i++)
            display_l(name[index[i]]);
        break;

    case PARAM_A + PARAM_R + PARAM_r + PARAM_f:
    case PARAM_A + PARAM_R + PARAM_f:
    case PARAM_A + PARAM_R + PARAM_r:
    case PARAM_A + PARAM_R:
        for(i = 0; i < count; i++)
                display_single(name[index[i]]);
        
        for(i = 0; i < count; i++)
            if((strcmp(name[index[i]],".") != 0) && (strcmp(name[index[i]],"..") != 0))
                display_R_single(name[index[i]]);
        break;
    
    case PARAM_R + PARAM_L + PARAM_r + PARAM_f:
    case PARAM_R + PARAM_L + PARAM_f:
    case PARAM_R + PARAM_L + PARAM_r:
    case PARAM_R + PARAM_L:
        for(i = 0; i < count; i++)
            if(name[index[i]][0] != '.')
                display_l(name[index[i]]);
        
        for(i = 0; i < count; i++)
            if(name[index[i]][0] != '.')
                display_R_l(name[index[i]]);
        break;
    
    case PARAM_A + PARAM_L + PARAM_R + PARAM_r + PARAM_f:
    case PARAM_A + PARAM_L + PARAM_R + PARAM_f:
    case PARAM_A + PARAM_L + PARAM_R + PARAM_r:
    case PARAM_A + PARAM_L + PARAM_R:
        for(i = 0; i < count; i++)
                display_l(name[index[i]]);
        
        for(i = 0; i < count; i++)
            if((strcmp(name[index[i]],".") != 0) && (strcmp(name[index[i]],"..") != 0))
                display_R_l(name[index[i]]);
        break;
    default:
        break;
    
    }
}

//对文件名排序
void quickSort(char **array, int left, int right)
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
    //char filenames[256][PATH_MAX + 1];
    int i,j,len;
    
    //-d
    if(flag_param & PARAM_d)
    {
        if(flag_param & PARAM_L)
            display_l(path);
        else
        {
            display_single(path);
            printf("\n");
        }
        return;
    }

    if((flag_param & PARAM_R) != 0)
    {
        //要考虑全面一些
        len = strlen(PATH);
        if(len > 0)
        {
            if(PATH[len - 1] == '/')
                PATH[len - 1] = '\0';
        }
        if((path[0] == '.' || path[0] == '/') && flag == 0)
        {
            strcat(PATH,path);
            flag++;
        }
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
    
    g_maxlen = 0;
    while((ptr = readdir(dir)) != NULL)
    {
        if(g_maxlen < strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);
    
    //动态分配空间，减少栈的消耗
    char **filenames = (char **)malloc(sizeof(char *) * count);
    memset(filenames,0,sizeof(char *) * count);
    for(i = 0; i < count; i++)
    {
        filenames[i] = (char *)malloc(sizeof(char) * g_maxlen + 1);
        memset(filenames[i],0,sizeof(char) * g_maxlen + 1);
    }

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
    if(!(flag_param & PARAM_f))
        quickSort(filenames,0,count - 1);

    //切换工作目录
    if(chdir(path) < 0)
        my_err("chdir",__LINE__);

    display(filenames,count);

    
    //释放空间
    if(flag_param & PARAM_R)
        free(filenames);
    else
    {
        for(i = 0; i < count; i++)
            free(filenames[i]);
        free(filenames);
    }

    if(!(flag_param & PARAM_L) && !(flag_param & PARAM_R))
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
        else if(param[i] == 'r')
        {
            flag_param |= PARAM_r;
            continue;
        }
        else if(param[i] == 'd')
        {
            flag_param |= PARAM_d;
            continue;
        }
        else if(param[i] == 'f')
        {
            flag_param |= PARAM_f;
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
            if(flag_param & PARAM_L)
                display_l(path);
            else
            {
                display_single(path);
                printf("\n");
            }
            i++;
        }
    }while(i < argc);
    
    return 0;
}
