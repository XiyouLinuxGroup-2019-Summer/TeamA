#include "client.h"

void my_err(const char * err_string, int line)
{
    fprintf(stderr, "line;%d", line);
    perror(err_string);
    exit(1);
}
