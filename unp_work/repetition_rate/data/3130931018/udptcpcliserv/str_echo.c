#include"unp.h"
void
str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	for(;;)
	{
		if((n = read(sockfd,line,MAXLINE)) == 0)
		{
			return;
		}
		Writen(sockfd,line,n);
	}
}
