#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char *argv[],char **environ)
{
    int i;
    printf(" i am a process image!\n");
    printf("my pid = %d,parrntpid = %d\n",getpid(),getppid());
    printf("uid = %d,gid = %d\n",getuid(),getgid());

    for(i=0;i<argc;i++)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    return 0;
}
