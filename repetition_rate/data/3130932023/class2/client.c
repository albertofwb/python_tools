#include "unp.h"
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int  sockfd;
    struct sockaddr_in serveraddr;
   
    if(argc != 2)
        err_sys("no ip address");
  
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));   
 
    //name the socket
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(32023);
    //Inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

    connect(sockfd, (SA *)&serveraddr, sizeof(serveraddr));
 
    str_cli(stdin, sockfd);
     

    exit(0);
}





