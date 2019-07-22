#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    switch(pid)
    {
        case 0:
            while(1)
            {
                printf("A background process:\n pid : %d\n parentid: %d\n",getpid(),getppid());
                sleep(10);
            }
        case -1:
            perror("process creaation failed!\n");
            exit(-1);
        default:
            printf("i am parent process,my pid is %d\n",getpid());
            exit(0);
    }
    return 0;
}
