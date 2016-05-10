#include "unp.h"
#include <time.h>

int main(int argc, char ** argv){
	int listenfd,connfd;
	struct sockaddr_in sockaddr;
	time_t ticks;
	char buff[MAXLINE];	

	listenfd = Socket(AF_INET,SOCK_STREAM,0);
    
	bzero(&sockaddr, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(31052);

	Bind(listenfd, (SA*)&sockaddr,sizeof(sockaddr));

	Listen(listenfd,LISTENQ);

	for(; ;){
		connfd = Accept(listenfd,(SA*)NULL,NULL);
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s",ctime(&ticks));
		Write(connfd,buff,strlen(buff));
		Close(connfd);
	}
}
