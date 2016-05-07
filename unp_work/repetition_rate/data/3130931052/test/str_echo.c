#include "unp.h"

void str_echo(int connfd){
	
	ssize_t n;
	char line[MAXLINE];

	if((n = Readline(connfd,line,MAXLINE)) == 0){
	return ;
	}
	printf("%s\n",line);
	Write(connfd,line,MAXLINE);
	

}
