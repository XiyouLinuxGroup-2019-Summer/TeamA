#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
int argcount;//命令个数
int find_command(char *);
char PATH[PATH_MAX+1] = "/home";//路径
char PATHTEMP[PATH_MAX+1];

void print(char* test)
{
    char name[100];
    gethostname(name,100);
  //  printf("\033[36;1mhello!@%s:\033[0m",name);
    getcwd(PATH,100);
  //  printf("\033[34;1m%s$ \033[0m",PATH);
    sprintf(test,"\033[36;1mhello!@%s:\033[0m\033[34;1m%s$ \033[0m" ,name, PATH) ;
    
    return  ;
}

void get_put(char *buf, const char*path)
{
    char ch;
    int len = 0;

    char *str = readline(path);
    strcpy(buf,str);
    add_history(buf);
   

   /* while(len<256 && (ch=getchar()) != '\n')
    {
        buf[len++] = ch;
    }
    buf[len++] = '\n';
    buf[len] = '\0';

    if(len >= 256)
    {
        printf("命令过长！\n");
        exit(-1);
    }*/
}

void explain_input(char *buf,char arglist[100][256])
{
    char *p = buf;
    char *q = buf;
    int number = 0;

    while(1)
    {
        if(p[0] == '\0')
        {
            break;
        }
        if(p[0] == ' ')
        {
            p++;
        }
        else
        {
            q = p;
            number = 0;
            while((q[0] != ' ') && (q[0] != '\0'))
            {
                number++;
                q++;
            }
            strncpy(arglist[argcount],p,number);
            arglist[argcount][number] = '\0';
            //puts(arglist[argcount]);

            argcount++;
            p = q;
        }
    }
   /* for(int i = 0;i<argcount;i++)
    {
        printf("解析  %s\n",arglist[i]);
    }*/
}

void do_cmd(int argcount,char arglist[100][256])
{
    int flag = 0; //><| 用于个数的判断
    int how = 0; //<>|种类的判断
    int background = 0; //&有无的判断
    
    int status;
    int pid; //接收fork
    int fd; //
    int t;

    char *arg[argcount+1]; //取出的命令
    char *argnext[argcount+1]; //|时用，
    char *file;

    int i;
    for(i=0;i<argcount;i++)
    {
        arg[i] = (char *)arglist[i];
    }
    arg[argcount] = NULL;
    
    if(strcmp(arg[0],"ls") == 0)
    {
        arg[argcount] = "--color=auto";
        arg[argcount+1] = NULL;
    }
    if(strcmp(arg[0],"cd") == 0)
    {
        getcwd(PATH,100);
        if((argcount == 1) || strcmp(arg[1],"~") == 0)
        {
            strcpy(PATHTEMP,PATH);
            strcpy(PATH,"/home");
            chdir(PATH);
        }
        else if(strcmp(arg[1],"-") == 0)
        {
            chdir(PATHTEMP);
            strcpy(PATHTEMP,PATH);
        }
        else
        {
            t = chdir(arg[1]);
            if(t == -1)
                printf("切换目录失败,该目录下没有此文件!\n");
            strcpy(PATHTEMP,PATH);
        }
        return;
    }

    for(i=0;i<argcount;i++) //判断有无&
    {
        if(strncmp(arg[i],"&",1) == 0)
        {
       //     printf("aaa\n");
            if(i==argcount-1)
            {
                background = 1;
                arg[argcount-1] = NULL;
                break;
            }
            else
            {
                printf("错误的输入命令！\n");
                return;
            }
        }
    }

    for(i=0;i<argcount;i++)
    {
        if(arg[i] != NULL && strcmp(arg[i],">") == 0) //> ---1
        {
            flag++;
            how = 1;
            if(arg[i+1] == NULL)
            {
                flag++;
            }
        }
        if(arg[i] != NULL && strcmp(arg[i],">>") == 0)
        {
            flag++;
            how = 4;
            if(arg[i+1] == NULL)
                flag++;
        }
        if(arg[i] != NULL && strcmp(arg[i],"<") == 0) //< ---2
        {
            flag++;
            how = 2;
            if(i == 0)
            {
                flag++;
            }
        }
        if(arg[i] != NULL && strcmp(arg[i],"<<") == 0)
        {
            flag++;
            how = 5;
            if(arg[i] == 0)
                break;
        }
        if(arg[i] != NULL && strcmp(arg[i],"|") == 0) //| ---3
        {
            flag++;
            how = 3;
            //printf("how = %d\n",how);
            if(i == 0 || arg[i+1] == NULL)
            {
                flag++;
            }
        }
    }
    if(flag > 1)
    {
        printf("wrong command!\n");
        return;
    }

    if(how == 1)
    {
        for(i=0;arg[i] != NULL;i++)
        {
            if(strcmp(arg[i],">") == 0)
            {
                file = arg[i+1]; //?
                arg[i] = NULL;
            }
        }
    }
    if(how == 4)
    {
   char name[100];
     for(i=0;arg[i] != NULL;i++)
            if(strcmp(arg[i],">>") == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }
    if(how == 2)
    {
        for(i=0;arg[i] != NULL;i++)
        {
            if(strcmp(arg[i],"<") == 0)
            {
                file = arg[i+1]; //?
                arg[i] = NULL;
            }
        }
    }
    if(how == 5)
    {
        for(i=0;arg[i] != NULL;i++)
            if(strcmp(arg[i],"<<") == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }
    if(how == 3)
    {
        for(i=0;arg[i] != NULL;i++)
        {
           if(strcmp(arg[i],"|") == 0) 
           {
                arg[i] = NULL;
                int j;
                for(j=i+1;arg[j] != NULL;j++)
                {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = NULL;
                break;
           }
        }
    }

    if((pid = fork()) < 0)
    {
        printf("fork error!\n");
        return;
    }


    switch(how)
    {
        case 0:
            if(pid == 0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s : command is not found!\n",arg[0]);
                    exit(0);
                }
                execvp(arg[0],arg); 
                exit(0);
            }
            break;
        case 1:
            if(pid == 0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s : command is not found!\n",arg[0]);
                    exit(0);
                }

                fd = open(file,O_RDWR | O_CREAT |O_TRUNC,0644);
                dup2(fd,1);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 4:
            if(pid == 0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s : command is not found!\n",arg[0]);
                    exit(0);
                }
                fd = open(file,O_RDWR | O_CREAT | O_APPEND);
                dup2(fd,1);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 2:
            if(pid == 0)
            {
                if(!(find_command(arg[0])))
                {   
                    printf("%s : command is not found!\n",arg[0]);
                    exit(0);
                }

                fd = open(file,O_RDONLY);
                dup2(fd,0);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 5:
        if(pid == 0)
        {
            if(!(find_command(arg[0])))
            {
                printf("%s : command is not found!\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDONLY);
            dup2(fd,0);
            execvp(arg[0],arg);
            exit(0);
        }
        break;
        case 3:
            if(pid == 0)
            {
                int pid2;
                int status2;
                int fd2;
                
                if((pid2 = fork()) < 0)
                {
                    printf("fork2 error!\n");
                    return;
                }
                else if(pid2 == 0)
                {
                    if(!(find_command(arg[0])))
                    {
                        printf("%s : command is not found!\n",arg[0]);
                        exit(0);
                    }
                    fd2 = open("/tmp/my_shell_file",O_WRONLY | O_CREAT | O_TRUNC , 0644);

                    dup2(fd2,1);
                    execvp(arg[0],arg);

                    exit(0);
                }

                if(waitpid(pid2,&status2,0) == -1)
                {
                    printf("wait for child process error!\n");
                }
                if(!(find_command(argnext[0])))
                {
                    printf("%s : command is not found!\n",argnext[0]);
                    exit(0);
                }

                fd2 = open("/tmp/my_shell_file",O_RDONLY);
                
                dup2(fd2,0);
                execvp(argnext[0],argnext);
                //getchar();
                if(remove("/tmp/my_shell_file"))
                    printf("remove error!\n");
                exit(0);
            }
            break;
        default:
            break;
    }

    if(background == 1) //父进程不等子进程 &
    {
        printf(" process id : %d \n",pid);
        return;
    }
    if(waitpid(pid,&status,0) == -1)
    {
        printf("wait for child process error!\n");
    }
}


int find_command(char *command)
{
    DIR *dp;
    struct dirent *dirp;
    char *path[] = {"./" , "/bin" , "/usr/bin" , NULL};

    if(strncmp(command,"./",2) == 0)
    {
        command += 2;
    }
    int i = 0;
    while(path[i] != NULL)
    {
        if((dp = opendir(path[i])) == NULL)
        {
            printf("can not open /bin !\n");
        }
        while((dirp = readdir(dp)) != NULL)
        {
            if(strcmp(dirp->d_name,command) == 0)
            {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}


int main()
{
    signal(SIGINT, SIG_IGN);
    char *buf = NULL; // 录入命令
    char arglist[100][256]; //存贮命令

    buf = (char *)malloc(256);
    if(buf == NULL)
    {
        perror("malloc error!\n");
        exit(-1);
    }
  //  getcwd(PATH,100);
    while(1)
    {
        memset(buf,0,256);
        char test[1024] ;
        print(test); //提示符
       /* char name[100];
        gethostname(name,100);
        printf("\033[36;1mhello!@%s:\033[0m",name);
        getcwd(PATH,100);
        printf("\033[34;1m%s$ \033[0m",PATH);

      
      
        char *str = readline("");
        strcpy(buf,str);
        add_history(buf);
*/
        
        //getchar();

        get_put(buf, test); //录入命令于buf里
        //getchar();    
 //       fflush(stdin);
      //  printf("%s===\n",buf);
        if(strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0 )
            break;
        //getchar();
        for(int i=0;i<100;i++)
        {
            arglist[i][0] = '\0';
        }
        argcount = 0;
        //getchar();
        explain_input(buf,arglist);//解析命令，存在arglist里
        //getchar();
        do_cmd(argcount,arglist); //执行命令
    }
    if(buf != NULL)
    {
        free(buf);
        buf = NULL;
    }
    return 0;
}
