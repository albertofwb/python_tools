# include "unp.h"
# include "mul_cmg.h"

void str_echo(int sockfd){
	ssize_t n;
   //char line[MAXLINE];
   	struct parameter p;
	struct result result;
	for( ; ; ){
		if((n=Readline(sockfd,&p,sizeof(p)))==0){
			return ;
		}
		result.result=p.x*p.y;
		Writen(sockfd,&result,sizeof(result));
	}
}
