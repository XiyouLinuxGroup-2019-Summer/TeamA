#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    pid_t pid;
    char *msg;
    int k;
    int exit_code;

    printf("Study how to get exit code\n");
    pid = fork();
    switch(pid)
    {
    case 0:
        msg = "chind";
        k = 5;
        exit_code = 37;
        break;
    case -1:
        perror("failed\n");
        exit(1);
    default:
        exit_code = 0;
        break;
    }

    if(pid != 0)
    {
        int stat_val;
        pid_t chind_pid;
        chind_pid = wait(&stat_val);
        
        printf("chind process has exited, pid = %d\n",chind_pid);
        if(WIFEXITED(stat_val))
            printf("chind exited with code %d\n",WEXITSTATUS(stat_val));
        else
            printf("chind exited abnormaly\n");
    }
    else
        while(k--)
        {
            puts(msg);
            sleep(1);
        }
    return 0;
}

