#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

void sig_child(int sig)
{
    pid_t pid;
    int stat;
    while((pid=waitpid(-1,&stat,WNOHANG))>0)
        printf("child %d terminated\n",pid);
    return;
}

int main()
{
    int sockfd,connfd;
    struct sockaddr_in addr,cddr;
    memset(&addr,0,sizeof(addr));
    memset(&cddr,0,sizeof(cddr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(32034);
    addr.sin_addr.s_addr = inet_addr("101.200.160.104");
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    listen(sockfd,5);

    while(1)
   {
       int len = sizeof(cddr);
       pid_t pid;
       connfd = accept(sockfd,(struct sockaddr*)&cddr,&len);
       if((pid=fork()) == 0)
       {
           char recvline[512] = {0};
           while(1)
          {
           	recv(connfd,recvline,511,0);
           	printf("%s\n",recvline);
           	send(sockfd,"OK",2,0);
          }
           close(connfd);
           exit(0);
       }
       close(connfd);
   }
   close(sockfd);
}
