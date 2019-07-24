#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>                 //获取用户信息（struct passwd * ）
#include<grp.h>
#include<readline/readline.h>   //readline库
#include<readline/history.h>

#define normal 0        //一般的命令
#define out_redirect 1  //输出重定向 >
#define in_redirect 2   //输入重定向 <
#define have_pipe 3     //命令中有管道 |
#define out_redirects 4 // >>

void print_prompt();    //打印提示符
void get_input(char *, int *, char (*)[256]); //得到输入的命令
void explain_input(char *, int *, char (*)[256]);  //对输入命令进行解析
void do_cmd(int, char (*)[256], int, char (*)[256]);   //执行命令
int find_command(char *);       //查找命令中的可执行程序

char w_cd[100];     // cd -：记录上次的目录路径

int main()
{
    signal(SIGINT,SIG_IGN);     //防止被ctrl + c中断
    
    int i;
    int argcount = 0;           //记录命令中的参数个数
    char arglist[100][256];     //储存命令
    int historycount = 0;       //记录历史命令数目
    char history[100][256];     //储存历史命令
    char *buf = NULL;
    
    memset(arglist,0,sizeof(arglist));
    memset(history,0,sizeof(history));

    buf = (char *)malloc(sizeof(char) * 256);
    if(buf == NULL)
    {
        perror("malloc failed");
        exit(-1);
    }

    while(1)
    {
        //将buf所指向的空间清零
        memset(buf,0,sizeof(buf));
        print_prompt();
        get_input(buf,&historycount,history);

       //若输入的命令为exit 或 logout 则退出程序
        if(strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0)
            break;
        for(i = 0; i < 100; i++)
            arglist[i][0] = '\0';
        argcount = 0;
        
        explain_input(buf,&argcount,arglist);
        do_cmd(argcount,arglist,historycount,history);
    }

    if(buf != NULL)
    {
        free(buf);
        buf = NULL;
    }
    
    exit(0);
}

void print_prompt()
{
    uid_t uid;
    struct passwd *pw;
    char buf[100];

    uid = getuid();
    pw = getpwuid(uid);
    getcwd(buf,100);    //获取目录路径

    //颜色
    printf("\e[1;32m%s@lyp\e[0m",pw->pw_name);
    printf(":");
    printf("\e[1;34m%s\e[0m",buf);
    printf("$ ");
}

void get_input(char *buf, int *historycount, char history[][256])
{
    int len;
    
    //重点在这里
    char * buf1 = readline("");
    strcpy(buf,buf1);
    
    len = strlen(buf);
    if(len == 0)
        return;
    if(*historycount == 0)
    {
        strcpy(history[*historycount],buf);
        add_history(buf);
        *historycount = *historycount + 1;
    }
    else
    {
        if(strcmp(history[*historycount - 1],buf) == 0)
        {
            add_history(buf);
        }
        else
        {
            strcpy(history[*historycount],buf);
            add_history(buf);
            *historycount = *historycount + 1;
        }
    }
}

void explain_input(char *buf, int *argcount, char arglist[][256])
{
    char *p = buf;
    char *q = buf;
    int number = 0;

    while(1)
    {
        if(p[0] == '\0')
            break;
        if(p[0] == ' ')
            p++;
        else
        {
            q = p;
            number = 0;
            while((q[0] != ' ') && (q[0] != '\0'))
            {
                number++;
                q++;
            }
            strncpy(arglist[*argcount],p,number + 1);   //解析命令
            arglist[*argcount][number] = '\0';
            
            *argcount = *argcount + 1;  
            p = q;
        }
    }
}

void do_cmd(int argcount, char arglist[][256], int historycount, char history[][256])
{
    int flag = 0;
    int how = 0;        //用于指示命令中是否含有>,<,|
    int background = 0; //标识命令中是否有后台运行标识符 &
    int status,i,fd;
    char *arg[argcount + 1];
    char *argnext[argcount + 1];
    char *file;
    pid_t pid;

    //将命令取出
    for(i = 0; i < argcount; i++)
        arg[i] = (char *)arglist[i];
    arg[argcount] = NULL;

    //查看命令行是否有后台运行符
    for(i = 0; i < argcount; i++)
    {
        if(strcmp(arg[i],"&") == 0)
        {
            if(i == argcount - 1)
            {
                background = 1;
                arg[argcount - 1] = NULL;
                break;
            }
            else
            {
                printf("wrong command\n");
                return;
            }
        }
    }
    
    // cd
    if(strcmp(arg[0],"cd") == 0)  
    {
        char temp[100] = "/home/liyupeng";
        char buf[100];
        memset(buf,0,sizeof(buf));
        getcwd(buf,100);

        if(arg[1] == NULL || !strcmp(arg[1],"~" ))
        {
            strcpy(w_cd,buf);
            chdir(temp);
            return;
        }
        else if(!strcmp(arg[1],"-"))
        {
            printf("%s\n",w_cd);
            chdir(w_cd);
            return;
        }
        else 
        {
            strcpy(w_cd,buf);
            chdir(arg[1]);
            return;
        }
    }

    // history
    if(strcmp(arg[0],"history") == 0)
    {
        for(i = 0; i < historycount; i++)
            printf("%d %s\n",i + 1, history[i]);
        return;
    }

    //查看命令行是否有重定向或管道（格式是否正确）
    for(i = 0; arg[i] != NULL; i++)
    {
        if(strcmp(arg[i],">") == 0)
        {
            flag++;
            how = out_redirect;
            if(arg[i + 1] == NULL)
                flag++;
        }

        if(strcmp(arg[i],">>") == 0)
        {
            flag++;
            how = out_redirects;
            if(arg[i + 1] == NULL)
                flag++;
        }

        if(strcmp(arg[i],"<") == 0)
        {
            flag++;
            how = have_pipe;
            if(i == 0)
                flag++;
        }

        if(strcmp(arg[i],"|") == 0)
        {
            flag++;
            how = have_pipe;
            if(arg[i + 1] == NULL)
                flag++;
            if(i == 0)
                flag++;
        }
    }

    if(flag > 1)
    {
        printf("wrong command\n");
        return;
    }

    // >
    if(how == out_redirect)
    {
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i],">") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }    
        }
    }

    // >>
    if(how == out_redirects)
    {
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i],">>") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }    
        }
    }
    
    // <
    if(how == in_redirect)
    {
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i],"<") == 0)
            {
                file = arg[i + 1];
                arg[i] = NULL;
            }    
        }
    }
    
    // |
    if(how == have_pipe)
    {
        //将管道后面的部分存入argnext中，管道后面是一个可执行的shell命令
        for(i = 0; arg[i] != NULL; i++)
        {
            if(strcmp(arg[i],"|") == 0)
            {
                arg[i] = NULL;
                int j;
                for(j = i + 1; arg[j] != NULL; j++)
                    argnext[j - i - 1] = arg[j];
                argnext[j - i - 1] = arg[j];    //最后 == NULL
                break;
            }    
        }
    }
    
    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        return;
    }

    switch(how)
    {
    case 0:
        if(pid == 0)
        {
            if(!(find_command(arg[0])))
            {
                printf("%s: command not found\n",arg[0]);
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
                printf("%s: command not found\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
            
            //系统调用（ > ）
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
                printf("%s: command not found\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDONLY);
            
            //系统调用（ < ）
            dup2(fd,0);
            execvp(arg[0],arg);
            exit(0);
        }
        break;
    case 3:
        if(pid == 0)
        {
            int pid2;
            int fd2;
            int status_2;

            if((pid2 = fork()) < 0)
            {
                printf("fork2 error\n");
                return;
            }
            else if(pid2 == 0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s: command not found\n",arg[0]);
                    exit(0);
                }

                //打开文件，将屏幕输出流入该文件
                fd2 = open("/tmp/testfile",O_WRONLY|O_CREAT|O_TRUNC,0644);
                
                //复制文件描述符（ > ）
                dup2(fd2,1);
                execvp(arg[0],arg);
                exit(0);
            }

            if(waitpid(pid2,&status_2,0) == -1)
                printf("wait for child process error\n");

            if(!(find_command(argnext[0])))
            {
                printf("%s: command not found\n",argnext[0]);
                exit(0);
            }

            fd2 = open("/tmp/testfile",O_RDONLY);
            dup2(fd2,0);
            execvp(argnext[0],argnext);

            if(remove("/tmp/testfile"))     //删除文件
                printf("remove error");
            exit(0);
        }
        break;
    case 4:
        if(pid == 0)
        {
            if(!(find_command(arg[0])))
            {
                printf("%s: command not dound\n",arg[0]);
                exit(0);
            }
            fd = open(file,O_RDWR|O_CREAT|O_APPEND);

            // >>
            dup2(fd,1);
            execvp(arg[0],arg);
            exit(0);
        }
    default:
        break;
    }
    
    //若命令中有 &，表示后台执行，父进程直接返回，不等待子进程结束
    if(background == 1)
    {
        printf("process id %d\n",pid);
        return;
    }

    //父进程等待子进程结束
    if(waitpid(pid,&status,0) == -1)
        printf("wait for child process error\n");
}

int find_command(char *command)
{
    DIR *dir;
    struct dirent *ptr;
    char *path[] = {"./","/bin","/usr/bin",NULL};   //在这些路径中寻找可执行程序

    int i = 0;

    //使当前目录下的程序可以运行
    if(strncmp(command,"./",2) == 0)
        command = command + 2;

    //分别在当前目录，/bin，/usr/bin 目录查找
    while(path[i] != NULL)
    {
        if((dir = opendir(path[i])) == NULL)
            printf("can not open /bin \n");
        while((ptr = readdir(dir)) != NULL)
        {
            if(strcmp(ptr->d_name,command) == 0)
            {
                closedir(dir);
                return 1;
            }
        }
        closedir(dir);
        i++;
    }
    return 0;
}
