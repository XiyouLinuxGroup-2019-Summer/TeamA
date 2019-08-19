#include <stdio.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#pragma comment(lib, "libmysql.lib") 

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z)) 
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))  
#define FF(a,b,c,d,x,s,ac) { a += F(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define GG(a,b,c,d,x,s,ac) { a += G(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define HH(a,b,c,d,x,s,ac) { a += H(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define II(a,b,c,d,x,s,ac) { a += I(b,c,d) + x + ac;  a = ROTATE_LEFT(a,s); a += b; }
#define PORT 1212


typedef struct{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;


typedef struct {                                                                                                                               
     int type;
     int ans;
     char login_name[256];
     char send_name[256];   
     char recv_name[256];   
     int send_fd;           
     int recv_fd;           
     char message[256];     
     char file[30000];
}pack;

typedef struct Node{
    int fd;
    char name[256];
    struct Node *next;
}node;

int sock_fd, conn_fd;
MYSQL mysql;
node *head;
pack send_array[200];
int num_send_pack;

void MD5Init(MD5_CTX *context);  
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen);  
void MD5Final(MD5_CTX *context,unsigned char digest[16]);  
void MD5Transform(unsigned int state[4],unsigned char block[64]);  
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len);  
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len);
int Md5(char *password, char *pass_word);
void registe(pack *recv);
void login(pack *recv);
void mysql_init_t();
void *work(void *recv);
void my_err(const char * err_string, int line);
void add (node**Head, int fd_t, char *nam);
void fre (node *Head);
void delet ( node **Head, int fd_t );
void addfriend(pack *recv);
void deletefriend(pack *recv);
void chatgroup(pack *recv);
int search( node *Head, char *nam );
void showfriends(pack *recv); 
void creategroup(pack *recv);
void addgroup(pack *recv);
void sendfile(pack *recv);
void inviteperson(pack *recv);
void chatone(pack *recv);
void showgroups(pack *recv);
void kickperson(pack *recv);
void quitgroup( pack *recv );
