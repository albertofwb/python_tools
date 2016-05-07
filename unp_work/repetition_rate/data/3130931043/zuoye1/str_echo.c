#include "unp.h"


void str_echo(int sockfd)
{
	ssize_t n;

	long arg1,arg2;
	
	char line[MAXLINE];

	while(1){
		if (0==(n=Readline(sockfd,line,MAXLINE))){
			return;
		}
		if (2==(sscanf(line,"%ld%ld",&arg1,&arg2))){
			snprintf(line,sizeof(line),"%ld\n",arg1*arg2);
		}
		else 
			snprintf(line,sizeof (line),"input error \n");
		n=strlen(line);
		Writen(sockfd,line,n);
	}
}
