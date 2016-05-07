#include "unp.h"

int main(int argc, char **argv){
	int connfd,sockfd;
	struct sockaddr_in sockaddr,cliaddr;
	pid_t childpid;
	socklen_t clilen;

	sockfd = Socket(AF_INET,SOCK_STREAM,0);
	
    bzero(&sockaddr,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(31052);

	Bind(sockfd,(SA*)&sockaddr,sizeof(sockaddr));
	Listen(sockfd,LISTENQ);

	for( ; ;){
		clilen = sizeof(cliaddr);
		connfd = Accept(sockfd,(SA*)&cliaddr,&clilen);

		if((childpid = fork()) == 0){
			Close(sockfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
}
