//替换进程映像的程序
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[], char ** environ)
{
    int i;

    printf("i am a process image!\n");
    printf("my pid = %d, parentpid = %d\n", getpid(), getppid());
    printf("uid = %d, gid = %d\n", getuid(), getgid());

    for ( i = 0; i < argc; i++ )
        printf("argv[%d]:%s\n", i, argv[i]);
}

//exec实例，这里使用execve函数
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[], char ** environ)
{
    pid_t pid;
    int stat_val;
    printf("Exec example\n");
    pid = fork();
    switch(pid) {
    case -1:
        perror("Process Creation failed\n");
        exit(1);
    case 0:
        peinrf("child process is running\n");
        printf("my pid = %d, parentpid = %d\n", getpid(), getppid());
        execve("processimage", argv, environ);
        printf("process never go to here!\n");
        exit(0);
    default :
        printf("parent process is running\n");
    }

    wait(&stat_val);  //使父进程等待子进程
    exit(0);
}

//当调用ｅｘｅｃｖｅ函数执行processimage后，原有的子进程映像被替代，将不再被执行
//子进程永远不会执行近下来的printf("process never go to here!\n")，因为子进程映像
//已经被新的执行映像所替代

