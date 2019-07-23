#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("process creation study:\n");
    pid = fork();
    switch(pid)
    {
        case 0:
            printf("children process is running! 子进程id: %d,父进程id: %d\n",pid,getppid());
            break;
        case -1:
            printf("process creation is failed\n");
            break;
        default:
            printf("parent process is running! 子进程id: %d,父进程id: %d\n",pid,getpid());
    }
    return 0;
}
