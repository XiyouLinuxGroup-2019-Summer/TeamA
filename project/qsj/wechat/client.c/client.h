#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#pragma comment(lib, "libmysql.lib") 

#define PORT 1212

typedef struct {
    int type;
    int ans;
    char login_name[256];
    char send_name[256];
    char recv_name[256];
    int send_fd;
    int recv_fd;
    char message[256];
    char file[1000];
}pack;

int conn_fd;
char username[256];
char chatname[256];
pack recv_array[100];
int num_recv_pack;

void registe();
int login();
void welcome();
int menu();
int get_choice(char *choice_t);
int function();
void work();
void my_err(const char * err_string, int line);
void *recv_pack(void *fd);
void addfriend();
void creategroup();
char *pas( char *s );
void add_friend(pack pack_t); 
void sendfile();
void send_file( pack pack_t );
void deletefriend();
void delete_friend(pack pack_t);
int getch1(void);
void deal_pack();
void showfriends();
void chatone();
void show_friends( pack pack_t );
void inviteperson();
void add_group( pack pack_t );
void chat_one( pack pack_t );
void addgroup();
void chatgroup();
void chat_group(pack pack_t);
