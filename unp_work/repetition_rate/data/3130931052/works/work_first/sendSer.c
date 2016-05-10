#include "unp.h"
int main(){
	int connfd,listenfd;
	socklen_t clien;
	pid_t childpid;
	struct sockaddr_in cliaddr,servaddr;
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(AF_INET);
	servaddr.sin_port = htons(31052);
	Bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);
	for( ; ;){
		connfd = Accept(listenfd,(SA*)&cliaddr,&clilen);
		if((childpid=Fork()) == 0)

	}
}
