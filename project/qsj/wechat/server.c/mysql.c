#include "server.h"

void mysql_init_t()
{
    if (NULL == mysql_init(&mysql)) {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        exit(-1);
    }
    if (!mysql_real_connect(&mysql, "localhost", "root", "qsj122833", "userinfo", 0, NULL, 0)) {
        printf("mysql_real_connect failure!\n");
        exit(-1);
    }
    mysql_set_character_set(&mysql, "utf8");
    printf("mysql connect success\n");
}
