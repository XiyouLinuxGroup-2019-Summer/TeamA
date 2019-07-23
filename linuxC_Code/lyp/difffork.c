#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int s = 5;

int main()
{
    pid_t pid;
    int a = 1;
    int i;
    printf("fork —— vfork\n");

    //pid = fork();
    pid = vfork();
    switch(pid)
    {
    case 0:
        i = 3;
        while(i-- > 0)
        {
            printf("Chind process is running\n");
            s++;
            a++;
            sleep(1);
        }
        printf("Chind's s = %d, a = %d\n",s,a);
        break;
    case -1:
        perror("failed\n");
        exit(1);
    default:
        i = 5;
        while(i-- > 0)
        {
            printf("Parent process is running\n");
            s++;
            a++;
            sleep(1);
        }
        printf("Parnet's s = %d, a = %d\n",s,a);
        exit(0);
    }
    return 0;
}

