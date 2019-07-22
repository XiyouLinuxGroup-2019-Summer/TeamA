#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    char *msg;
    int k;

    printf("process creation study:\n");
    pid = fork();
    switch(pid)
    {
        case 0:
            msg = "child process is running!";
            k = 3;
            break;
        case -1:
            perror("process creation failed!\n");
            break;
        default:
            msg = "parent process id running!";
            k = 5;
            break;
    }
    while(k>0)
    {
        puts(msg);
        sleep(1);
        k--;
    }
    return 0;
}
