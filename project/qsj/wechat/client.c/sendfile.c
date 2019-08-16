#include "client.h"

void sendfile()
{
     pack send_t;
     int sum = 0;
     int fd;

     printf("please enter the person's name which you want to send file:\n");
     scanf("%s", send_t.recv_name);
     printf("please enter the filename:\n");
     scanf("%s", send_t.message);
     send_t.type = 10;

     fd = open(send_t.message, O_RDONLY);

     sum = read(fd, send_t.file, sizeof(send_t.file));
     send_t.ans = sum;
     while ( sum != 0 ) {
         if (send(conn_fd, &send_t, sizeof(pack), 0) < 0 )
             my_err("send", __LINE__);
         sum = read(fd, send_t.file, sizeof(send_t.file));
         send_t.ans = sum;
         if ( sum < 0 )
             break;
         printf("******  sending  please don't touch  ******\n");
     }

}


void send_file( pack pack_t )
{
    int fd, sum = 0;

    fd = open(pack_t.message, O_CREAT | O_WRONLY | O_APPEND,0777);
    perror(pack_t.message);

    sum = write(fd, pack_t.file, pack_t.ans);
    printf("******  recving  please don't touch  ******\n");
    close(fd);
}
