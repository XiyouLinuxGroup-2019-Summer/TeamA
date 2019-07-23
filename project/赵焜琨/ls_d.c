#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>

#define PARAM_NONE 0
#define PARAM_A 1
#define PARAM_L 2
#define PARAM_R 4

#define MAXROWLEN 80
char PATH[PATH_MAX + 1]; //路径
int flag;
int g_leave_len = MAXROWLEN;
int g_maxlen;

void display_dir(char *path);

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",__LINE__);
    perror(err_string);
    exit(1);
}


void cprint(char *name,mode_t st_mode)  //传入文件名，mode_t --- 颜色输出
{
     if(S_ISLNK(st_mode))   
        printf("\033[1;36m%-*s\033[0m",g_maxlen,name);
    else if(S_ISDIR(st_mode)&&(st_mode&000777)==0777)   
        printf("\033[1;34;42m%-*s\033[0m",g_maxlen,name);
    else if(S_ISDIR(st_mode))
        printf("\033[1;34m%-*s\033[0m",g_maxlen,name);
    else if(st_mode&S_IXUSR||st_mode&S_IXGRP||st_mode&S_IXOTH) 
        printf("\033[1;32m%-*s\033[0m",g_maxlen,name);
    else
        printf("%-*s",g_maxlen,name);

}


void  display_attribute(char* name)  //传入文件名 --- -l格式打印
{
    struct stat buf;
    char buff_time[32];
    struct passwd* psd;  
    struct group* grp;                                                                     
    if(lstat(name,&buf)==-1)
    {
        my_err("stat",__LINE__);
    }
    if(S_ISLNK(buf.st_mode))
        printf("l");
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
    
    if(buf.st_mode&S_IRUSR)
        printf("r");
    else
        printf("-");
    if(buf.st_mode&S_IWUSR)
        printf("w");
    else
        printf("-");
    if(buf.st_mode&S_IXUSR)
        printf("x");
    else
        printf("-");
    
    if(buf.st_mode&S_IRGRP)
        printf("r");
    else
        printf("-");
    if(buf.st_mode&S_IWGRP)
        printf("w");
    else
        printf("-");
    if(buf.st_mode&S_IXGRP)
        printf("x");
    else
        printf("-");

    if(buf.st_mode&S_IROTH)
        printf("r");
    else
        printf("-");
    if(buf.st_mode&S_IWOTH)
        printf("w");
    else
        printf("-");
    if(buf.st_mode&S_IXOTH)
        printf("x");
    else
        printf("-");

    printf("  ");
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4ld ",buf.st_nlink);  
    printf("%-8s ",psd->pw_name);
    printf("%-8s ",grp->gr_name);

    printf("%6ld",buf.st_size);
    strcpy(buff_time,ctime(&buf.st_mtime));
    buff_time[strlen(buff_time)-1]='\0'; 
    printf("  %s  ",buff_time);
    cprint(name,buf.st_mode);
    printf("\n");
}


void displayR_attribute(char *name) //传入文件名 --- -lR，先display_...打印，再该函数递归
{
    struct stat buf;
    void display_dir(char *name);
    if(lstat(name,&buf) == -1)
    {
       // return;
       my_err("lstat",__LINE__);
    }
    if(S_ISDIR(buf.st_mode))
    {
        if((buf.st_mode & S_IRGRP) == 0 && (buf.st_mode & S_IROTH) == 0)
            return;

        display_dir(name);
        free(name);
        char *p = PATH;
        while(*++p);
        while(*--p != '/');
        *p = '\0';
        chdir("..");
        return;
    }
}


void display_signal(char *name) //传入文件名 --- 打印文件
{
    int len,i;
    struct stat buf;

    if(lstat(name,&buf) == -1)
    {
        return;
    }
    if(g_leave_len < g_maxlen)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }
    cprint(name,buf.st_mode);
//    for(i=0;i<len;i++)
  //  {
    //    printf(" ");
   // }
   // printf("  ");
    g_leave_len = g_leave_len - (g_maxlen+2);
}


void displayR_signal(char *name) //传入文件名 --- -R时打印文件名，调用display_dir
{
    int len;
    struct stat buf;

    if(lstat(name,&buf) == -1)
    {
        return;
    }
    if(S_ISDIR(buf.st_mode))
    {
        if((buf.st_mode & S_IRGRP) == 0 && (buf.st_mode & S_IROTH) == 0)                             
             return;

        printf("\n");
        g_leave_len = MAXROWLEN;
        display_dir(name);
        free(name);
        char *p = PATH;
        while(*++p);
        while(*--p != '/');
        *p = '\0';
        chdir("..");
    }
}

void display(char **name,int count) //传入文件名指针数组，文件个数
{
    switch(flag)
    {
        int i;
        case PARAM_NONE:
            for(i=0;i<count;i++)
            {
                if(name[i][0] != '.')
                {
                    display_signal(name[i]);
                }
            }
            printf("\n");
            break;
        case PARAM_A:
            for(i=0;i<count;i++)
            {
                display_signal(name[i]);
            }
            printf("\n");
            break;
        case PARAM_L:
            for(i=0;i<count;i++)
            {
                if(name[i][0] != '.')
                {
                    display_attribute(name[i]);
                }
            }
            break;
        case PARAM_R:
            for(i=0;i<count;i++)
            {
                if(name[i][0] != '.')
                {
                    display_signal(name[i]);
                }
            }
            printf("\n");
            for(i=0;i<count;i++)
            {
               // if(strcmp(name[i],".") == 0 || strcmp(name[i],"..") == 0)
                if(name[i][0] != '.') //排除. ..，防止死循环
                {
                    displayR_signal(name[i]);
                }
            }
            break;
        case PARAM_L +PARAM_A:
            for(i=0;i<count;i++)
            {
                display_attribute(name[i]);
            }
            break;
        case PARAM_A +PARAM_R:
            //printf("----------%s\n",name[0]);
            //printf("==========%s\n",name[1]);
            for(i=0;i<count;i++)
            {
                display_signal(name[i]);
            }
            printf("\n");
            for(i=0;i<count;i++)
            {
               // if(strcmp(name[i],".") != 0 || strcmp(name[i],"..") != 0)
                if(name[i][0] != '.')
             //if(name[i][0] == ',' && name[i][1] == '.' || name[i][0] == '.' && name[i][1] == '\0')
                //    continue;
               // else
                {
                    displayR_signal(name[i]);
                }
            }
            break;
        case PARAM_L +PARAM_R:
            for(i=0;i<count;i++)
            {
                if(name[i][0] != '.')
                {
                    display_attribute(name[i]);
                }
            }
            printf("\n");
            for(i=0;i<count;i++)
            {
                if(name[i][0] != '.')
                {
                    displayR_attribute(name[i]);
                }
            }
            break;
        case PARAM_A + PARAM_L +PARAM_R:
            for(i=0;i<count;i++)
            {
                display_attribute(name[i]);
            }
            for(i=0;i<count;i++)
            {
    
                if(name[i][0] != '.')
                {
                    displayR_attribute(name[i]);
                }
            }
            break;
        default:
            break;
    }
}


void display_dir(char *path) //传入目录名
{
    DIR *dir;
    struct dirent *ptr;
    int count = 0;

    if((flag & PARAM_R) != 0) //有-R --- 格式
    {
        int len = strlen(PATH);
        if(len>0)
        {
            if(PATH[len-1] == '/')
                PATH[len-1] == '\0';
        }
        if(path[0] == '.' || path[0] == '/')
        {
            strcat(PATH,path);
        }
        else
        {
            strcat(PATH,"/");
            strcat(PATH,path);
        }
        printf("%s:\n",PATH);
    }

    dir = opendir(path); //得文件数量，最长文件名长度
    if(dir == NULL)
    {
        my_err("opendir",__LINE__);
    }
    g_maxlen = 0;
    while((ptr = readdir(dir)) != NULL)
    {
        if(g_maxlen<strlen(ptr->d_name))
        {
            g_maxlen = strlen(ptr->d_name);
        }
        count++;
    }
    closedir(dir);

    char **filenames = (char **)malloc(sizeof(char*)*count); //动态数组分配空间
    char temp[PATH_MAX+1];
    for(int i=0;i<count;i++)
    {
        filenames[i] = (char *)malloc(sizeof(char)*PATH_MAX+1);
    }

    int i,j;
    dir = opendir(path); //获取目录下所有文件名，存到*filenames[]里
    for(i=0;i<count;i++)
    {
        ptr = readdir(dir);
        if(ptr == NULL)
        {
            my_err("readdir",__LINE__);
        }
        strcpy(filenames[i],ptr->d_name);
    }
    closedir(dir);
    
    for(i=0;i<count-1;i++) // 排序
    {
        for(j=0;j<count-1-i;j++)
        {
            if(strcmp(filenames[j],filenames[j+1]) > 0)
            {
                strcpy(temp,filenames[j]);
                strcpy(filenames[j],filenames[j+1]);
                strcpy(filenames[j+1],temp);
            }
        }
    }

    if(chdir(path) < 0)
    {
        my_err("chdir",__LINE__);
    }

    display(filenames,count); // --- 后

    if((flag & PARAM_L == 0 && !(flag | PARAM_R)))
        printf("\n");
}

int main(int argc,char *argv[])
{
    int i,j,k=0,num=0;
    char param[32]; //参数
    char *path[1]; //指针数组存路径 --- 后
    path[0] = (char *)malloc(sizeof(char)*(PATH_MAX+1));
    flag = 0;
    struct stat buf;

    for(i=1;i<argc;i++) //解参 --- 得param[]参数数组,
    {
        if(argv[i][0] == '-')
        {
            for(j=1;j<strlen(argv[i]);j++)
            {
                param[k] = argv[i][j];
                k++;
            }
            num++;
        }
    }
    param[k] = '\0';

    for(i=0;i<k;i++) //判断参数 --- 得输入参数的类型(int) --- alR
    {
        if(param[i]=='a')
            flag|=PARAM_A;
        else if(param[i]=='l')
            flag|=PARAM_L;
        else if(param[i]=='R')
            flag|=PARAM_R;
        else
        {
            printf("my_ls:invalid option -%c\n",param[i]);
            exit(0);
        }
    }

    if(num+1==argc) //未输入目录，显示当前目录
    {
        strcpy(path[0],".");
        display_dir(path[0]);
        return 0;
    }

    i=1;
    do //判断输入参数类型 --- 文件or目录 ---进行处理 --- 后
    {
        if(argv[i][0]=='-')
        {
            i++;
            continue;
        }
        else
        {
            strcpy(path[0],argv[i]);
            if(stat(argv[i],&buf)==-1)
            {
                my_err("stat",__LINE__);
            }
            if(S_ISDIR(buf.st_mode))  
            {
                display_dir(path[0]);
                i++;
            }
            else
            {
                display(path,1);
                i++;
            }
        }
    }while(i<argc);

    printf("\n");
    return 0;       
}
