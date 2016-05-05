#include "unp.h"
int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t	childpid;
	socklen_t clilen;
	struct sockaddr_in cli_addr,serv_addr;
	listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(32003);
	Bind(listenfd,(SA *)&serv_addr,sizeof(serv_addr));
	
	Listen(listenfd,LISTENQ);
	

	for(;;){
		clilen = sizeof(cli_addr);
		connfd = Accept(listenfd,(SA *)&cli_addr,&clilen);
		if((childpid = Fork()) == 0){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	
	}

}

void str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	for(;;){
		if((n = Readline(sockfd,line,MAXLINE)) == 0)
			return;
		Writen(sockfd,line,n);

	}

}









