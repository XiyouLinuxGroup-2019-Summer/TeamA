#include <stdio.h>
#include <unsitd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int fd;

    printf("uid study: \n");
    printf("process's uid = %d, euid = %d\n", getuid(), geteuid());

    if ( (fd = open("test.c", O_RDWR)) == -1 ) {
        printf("open failure, errni is %d : %s \n", errno, strerror(errno));
        exit(1);
    }
    else {
        printf("open sucessfully!\n");
    }

    close(fd);
    exit(0);
}


//setuid函数只有超级用户进程才能更改实际用户ID
//内核对进程存取文件的许可权的检查，是通过考查进程的有效用户ＩＤ来实现的。
//当进程的ｕｉｄ是ｒｏｏｔ用户时，如果调用ｓｅｔｕｉｄ更改ｅｕｉｄ，则此进程从此
//不再具有超级用户权限了。
