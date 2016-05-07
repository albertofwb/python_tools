#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
    char send[MAXLINE], recv[MAXLINE];
  
    //input the data from the screen
    while(1)
    {
        fgets(send, MAXLINE, fp);
        //write thre date
        //Writen(sockfd, send, strlen(send));
        write(sockfd, send, strlen(send));
        //the read it from the server
        if(Readline(sockfd, recv, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");

        Fputs(recv, stdout);           //output it on the scree
    }
}
