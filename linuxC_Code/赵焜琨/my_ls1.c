#include <stdio.h>
#include <dirent.h>
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
#include <sys/ioctl.h>
#define none "\e[0m"
#define red "\e[31m"
#define green "\e[32m"
#define blue "\e[34m"

#define MAXROWLEN 80;

int g_leave_len = MAXROWLEN; //剩余len
int g_max_len;

#define PARAM_NONE 0
#define PARAM_A 1
#define PARAM_L 2
#define PARAM_R 4

void my_err(const char *err,int line)
{
    printf(stderr,"line:%d",line);
    perror(err);
    exit(1);
}

void take(char *path,char *name)    //解名
{
    int i,j;
    for(i=0,j=0;i<strlen(path);i++)
    {
        if(path[i] == '/')
        {
            j=0;
            continue;
        }
        name[j++]=path[i];
    }
    name[j]='\0';
}

void dirplay_attribute(struct stat buf,char *name)
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
    printf("%3ld",buf.st_nlink);
    printf("%6s",pwd->pw_name);
    printf("%6s",grp->gr_name);
    printf("  %5ld",(long)buf.st_size);

    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)-1] == '\0';
    printf("  %s",buf_time);
   // printf("  %s",ctime(&buf.st_mtime));
   // printf("  %-s\n",name);
    if(S_ISDIR(buf.st_mode))
    {
        printf(blue "  %-s\n" none,name); 
    }
    else if(S_ISLNK(buf.st_mode))
    {
        printf(red "  %-s\n" none,name);
    } 
    else
    {
        printf("  %-s\n",name);
    }

                                                                        
}
void dirplay_signal(struct stat buf,char *name)
{
    int i,len;
    if(g_leave_len < g_max_len)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }
    len = strlen(name);
    len = g_max_len - len;
    if(S_ISDIR(buf.st_mode))
    {   
        printf(blue "%-s" none,name); 
    }   
    else if(S_ISLNK(buf.st_mode))                                                                        
    {   
        printf(red "%-s" none,name);
    }   
    else
    {   
        printf("%-s",name);
    }
    
    for(i=0;i<len;i++)
        printf(" ");
    printf("  ");
    g_leave_len -= (g_max_len+2);
}

 void dirplay(int flag,char *pathname)
 {
     void dirplay_R(int flag,char *path);

     struct stat buf;
     char name[NAME_MAX+1];
     int i,j=0;

     if(lstat(pathname,&buf)==-1)
     {
         my_err("lstat",__LINE__);
     }

     take(pathname,name); //解名

     switch(flag)
     {
         case PARAM_NONE:
            if(name[0] !='.')
            {
                 dirplay_signal(buf,name);
            }                 
            break;
        case PARAM_A:
            dirplay_signal(buf,name);
            break;
        case PARAM_L:
            if(name[0]!='.')
            {
                 dirplay_attribute(buf,name);
            }
            break;
         case PARAM_A + PARAM_L:
            dirplay_attribute(buf,name);
            break;
         case PARAM_R:
             dirplay_R(flag,pathname);
             break;
         case PARAM_A + PARAM_R: 
             {
                 printf(".  ..\n");
                 dirplay_R(flag,pathname);
                 break;
             }
         case PARAM_L + PARAM_R:
            {
                dirplay_attribute(buf,name);
                printf(" ");
                dirplay_R(flag,pathname);
            }
         case PARAM_A + PARAM_L + PARAM_R:
            {
                 dirplay_attribute(buf,".");
                 printf("  .\n");
                 dirplay_attribute(buf,"..");
                 printf("  ..\n");
                 dirplay_R(flag,pathname);
                 break;
            }
        }
 }

void dirplay_R(int flag,char *path) 
{
    struct stat buf;
    struct stat buff;
    DIR *dir;
    struct dirent *ptr;
    char name1[256][1000],name[256][1000],a[260],b[260];
    int i,j,k,len,count;

    if(lstat(path,&buf) == -1)
    {
        if(errno == 6)
        {
            return ;
        }
        else
        {
         //   printf("my_err di:  %s\n",path); 
            return ;
        }
    }


    if(S_ISDIR(buf.st_mode))    
    {
        printf("\n./%s:\n",path);  
        count = 0;
        dir = opendir(path);
        if(dir == NULL)
        {
            my_err("display_R",__LINE__);
        }

        i=0;
        while((ptr = readdir(dir))!=NULL)
        {
            len=0;
            count++;
            strncpy(name1[i],path,strlen(path));
            name1[i][strlen(path)]='/';
            name1[i][strlen(path)+1]='\0';
            strncat(name1[i],ptr->d_name,strlen(ptr->d_name));
            name1[i][strlen(name1[i])]='\0';

            i++;
        }

        for(i=0;i<count;i++)
            take(name1[i],name[i]);

        for(i=0;i<count;i++)
        {
            if(name[i][0] != '.')
            {

                if(lstat(name1[i],&buff) == -1)
                {
                    printf("error242");
                }
                if(S_ISDIR(buff.st_mode))
                   {
                       char *m=(char *)malloc(strlen(name1[i])*sizeof(char));
                        dirplay_R(flag,m);
                        free(m);
                   }

                else
                {
                    if(flag > 5)
                    {
                        dirplay_attribute(buff,name1[i]);
                    }
                    //printf("%s\t",name[i]);
                    dirplay_signal(buff,name[i]);
                }
            }
            else
            {
                continue;
            }
        }

    }
    else 
    {
        take(path,a);

        if(a[0] != '.')
        {
            if(flag > 5)
            {
                dirplay_attribute(buff,name1[i]);
            }
            printf("  %-s\t",a);
        }
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
                path[strlen(argv[i])] = '/';
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
