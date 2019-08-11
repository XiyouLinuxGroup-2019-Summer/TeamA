#include <stdio.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#pragma comment(lib, "libmysql.lib") 

#define PORT 1212

typedef struct {
    int choice;
    char name[256];
    char password[256];
    int send_fd;
    int recv_fd;
}userinfo;

typedef struct {
    int type;
    int ans;
    char send_name[256];
    char recv_name[256];
    int send_fd;
    int recv_fd;
    char message[256];
}pack;

int conn_fd;
char username[256];

void registe();
int login();
void welcome();
int menu();
int get_choice(char *choice_t);
int function();
void work();
void my_err(const char * err_string, int line);
void *recv_pack( void *fd );
void addfriend();
void add_friend( pack pack_t, int fd ); 
