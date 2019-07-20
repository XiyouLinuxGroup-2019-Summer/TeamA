#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
//  #include <Linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MAXROWLEN 80;
int g_leave_len = MAXROWLEN; //剩余len
int g_max_len;

#define PARAM_NONE 0
#define PARAM_A 1
#define PARAM_L 2
#define PARAM_R 3

void my_err(const char *err,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err);
    exit(1);
}

void dirplay_attritube(struct stat buf,char *name)
{
    char buf_time[100];
    struct passwd *pwd;
    struct group *grp;

    if(S_ISLNK(buf.st_mode))  //文件类型
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

    if(buf.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IROTH)
        printf("x");
    else
        printf("-");

    printf("  ");
    pwd=getpwuid(buf.st_uid);
    grp=getgrgid(buf.st_gid);
    printf("%-3ld",buf.st_nlink);
    printf("%-8s",pwd->pw_name);
    printf("%-8s",grp->gr_name);
    printf("%3ld",(long)buf.st_size);

    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)-1] == '\0';

    printf("  %s",buf_time);
    printf("%2s\n",name);

}                           

void dirplay_signal(char *name)
{
    int i,len;
    if(g_leave_len < g_max_len)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }
    len = strlen(name);
    len = g_max_len - len;
    printf("%-s",name);
    for(i=0;i<len;i++)
        printf(" ");
    printf("  ");
    g_leave_len -= (g_max_len+2);
}

void dirplay(int flag,char *pathname)
{
    struct stat buf;
    char name[NAME_MAX+1];
    int i,j=0;

    for(i=0;i<strlen(pathname);i++)  //解名
    {
        if(pathname[i] == '/')
        {
            j=0;
            continue;
        }
        name[j++]=pathname[i];
    }
    name[j]='\0';

    if(lstat(pathname,&buf) == -1)
    {
        my_err("lstat",__LINE__);
    }

    switch(flag)
    {
        case PARAM_NONE:
            if(name[0] != '.')
            {
                dirplay_signal(name);
            }
            break;
        case PARAM_A:
            dirplay_signal(name);
            break;
        case PARAM_L:
            if(name[0] != '.')
            {
                dirplay_attritube(buf,name);
            }
            break;
     //  case PARAM_R:
            //
        case PARAM_A + PARAM_L:
            dirplay_attritube(buf,name);
            printf("  %-s\n",name);
     //   case PARAM_A + PARAM_R:
            //
     //   case PARAM_L + PARAM_R:
            //
     //   case PARAM_A + PARAM_L + PARAM_R:
            //
    }
}

void dirplay_dir(int param_flag,char *path)
{
    DIR *dir;
    struct dirent *ptr;
    char name[256][PATH_MAX+1],temp[PATH_MAX+1];
    int count=0;

    dir=opendir(path);  //最长文件名
    if(dir == NULL)
    {
        my_err("opendir",__LINE__);
    }
    while((ptr = readdir(dir)) != NULL)
    {
        if(g_max_len < strlen(ptr->d_name))
        {
            g_max_len = strlen(ptr->d_name);
        }
        count++;
    }
    closedir(dir);
    if(count > 256)
    {
        my_err("too many files in this dir!",__LINE__);
    }
    int i,j,len=strlen(path);
    dir = opendir(path);
    for(i=0;i<count;i++)
    {
        ptr = readdir(dir);
        if(ptr == NULL)
        {
            my_err("readdir",__LINE__);
        }
        strncpy(name[i],path,len);
        name[i][len]='\0';
        strcat(name[i],ptr->d_name);
        name[i][len+strlen(ptr->d_name)] = '\0';
    }

    for(i=0;i<count-1;i++)
    {
        for(j=0;j<count-i-1;j++)
        {
            if(strcmp(name[j],name[j+1]) > 0)
            {
               strcpy(temp,name[j+1]);
               temp[strlen(name[j+1])] = '\0';
               strcpy(name[j+1],name[j]);
               name[j+1][strlen(name[j])] = '\0';
               strcpy(name[j],temp);
               name[j][strlen(temp)] = '\0';
            }
        }
    }
    for(i=0;i<count;i++)
    {
        dirplay(param_flag,name[i]);
    }
    closedir(dir);
    if((param_flag & PARAM_L) == 0 )
    {
        printf("\n");
    }
}


int main(int argc,char *argv[])
{
    char path[PATH_MAX+1]; //路径
    char param[100]; //参数
    int param_flag = PARAM_NONE;
    struct stat buf;

    int i,j=0,k;
    int num=0;
    for(i=1;i<argc;i++)  //解参
    {
        if(argv[i][0] == '-')
        {
            for(k=1;k<strlen(argv[i]);k++)
                {
                    param[j++] = argv[i][k];
                }
            num++;
        }
    }

    for(i=0;i<j;i++) //处理参数
    {
        if(param[i] == 'a')
        {
            param_flag |= PARAM_A;
            continue;
        }
        else if(param[i] == 'l')
        {
            param_flag |= PARAM_L;
            continue;
        }
        else if(param[i] == 'R')
        {
            param_flag |= PARAM_R;
            continue;
        }
        else
        {
            printf("my_ls : invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    param[j] = '\0';
    if(num == (argc-1))  //输入无目录
    {
        strcpy(path,"./");
        path[2] = '\0';
        dirplay_dir(param_flag,path);  //1
        return 0;
    }
    
    i=1;
    do
    {
        if(argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else
        {
            strcpy(path,argv[i]);
        }
        if(stat(path,&buf) == -1)
        {
            my_err("stat",__LINE__);
        }
        if(S_ISDIR(buf.st_mode))  //是目录
        {
            if(path[strlen(argv[i])-1] != '/')
            {
                path[strlen(argv[i])-1] = '/';
                path[strlen(argv[i])+1] = '\0';
            }
            else
            {
                path[strlen(argv[i])] = '\0';
            }
            dirplay_dir(param_flag,path);
            i++;
        }
        else  //文件
        {
            dirplay(param_flag,path);
            i++;
        }
    }while(i<argc);
    return 0;
}
