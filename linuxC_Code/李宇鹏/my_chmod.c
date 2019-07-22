#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc, char *argv[])
{
    int mode;   //权限
    int mode_u; //用户权限
    int mode_g; //所属组权限
    int mode_o; //其他用户权限
    char *path;

    //检查参数个数合法性
    if(argc < 3)
    {
        printf("%s <mode num> <target file>\n",argv[0]);
        exit(0);
    }

    //printf("%d\n",argc);
    //path = argv[0];
    //printf("%s\n",path);
    
    //获取命令行参数
    mode = atoi(argv[1]);
    //printf("%s %d\n",argv[1],mode);
    if(mode > 777 || mode < 0)
    {
        printf("mode num error!\n");
        exit(0);
    }
    mode_u = mode / 100;
    mode_g = (mode - (mode_u * 100)) / 10;
    mode_o = mode - (mode_u * 100) - (mode_g * 10);
    mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;    //八进制转换
    //printf("%d %d %d %o\n",mode_u,mode_g,mode_o,mode);
    path = argv[2];

    //printf("%s\n",path);
    
    if(chmod(path, mode) == -1)
    {
        perror("chmod error");
        exit(1);
    }

    return 0;
}
