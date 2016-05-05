#include"unp.h"
void str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	for(;;){
		if((n = readline(sockfd,line,MAXLINE)) == 0)
			return;
		writen(sockfd,line,n);
	}
}
