#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    
    printf("Process Creation Study\n");
    pid = fork();
    
    switch(pid) {
    case 0:
        printf("child process is running, childpid is %d, parentpid is %d\n", getpid(), getppid());
        break;
    case -1:
        printf("Process Creation failed\n");
        break;
    default:
        printf("parent process is running, childpid is %d, parentpid is %d\n", pid, getpid());
        break;
    }

    exit(0);
}
//父子进程是交替执行的，因为操作系统一般让所有进程享有同等的执行权，除非某些进程的优先级比其他的高。
