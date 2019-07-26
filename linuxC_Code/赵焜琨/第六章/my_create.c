#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int fd;
    if((fd = open("create_test",O_CREAT | O_EXCL | S_IWUSR)) == -1)
    {
        printf("laobee!\n");
        exit(1);
    }
    else
    {
        printf("successful,highbee!\n");
    }
    return 0;
}
