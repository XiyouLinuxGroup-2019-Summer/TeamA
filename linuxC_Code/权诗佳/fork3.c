#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    
    pid = fork();
    
    switch(pid) {
    case 0:
        while (1) {
            printf("A background is running, pid is %d, parentpid is %d\n", getpid(), getppid());
            sleep(3);
        }
    case -1:
        perror("Process Creation failed\n");
        exit(-1);
    default:
        printf("i am parent process, my pid is %d\n", getpid());
        exit(0);
    }

    return 0;
}

