#include "unp.h"

void

str_cli(FILE *fp,int sockfd)
{
      	char	sendline[MAXLINE],recvline[MAXLINE];
       int num1[MAXLINE],num2[MAXLINE];
	while (Fgets(sendline,MAXLINE,fp)!= NULL){
		Writen(sockfd,sendline,strlen(sendline));
		if(Readline(sockfd,recvline,MAXLINE)==0)
			err_quit("str_cli:server terminated prematurely");
		Fputs(recvline,stdout);
	}
	}
