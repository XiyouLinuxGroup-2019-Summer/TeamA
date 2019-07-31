#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *open_file(char *filename)
{
    FILE *stream;
    errno = 0;

    stream = fopen(filename,"r");
    if(stream == NULL)
    {
        printf("can not open this file %s , reason : %s\n",filename,strerror(errno));
        exit(-1);
    }
    else
        return stream;
}

int main()
{
    char *filename = "fish";
    open_file(filename);

    return 0;
}
