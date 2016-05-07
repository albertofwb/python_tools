#include "unp.h"


int main(int argc,char ** argv )
{
	int listenfd, connfd;
	pid_t chldpid;
	socklen_t clien;
	struct sockaddr_in cliaddr,servaddr;

	listenfd=Socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(31043);   //学号后五位

	Bind (listenfd,(SA*)&servaddr,sizeof (servaddr));

	Listen(listenfd,LISTENQ);

	while(1){
		clien=sizeof (cliaddr);

		connfd=Accept(listenfd,(SA*)&cliaddr,&clien);

		if ((chldpid=Fork()) == 0){
			Close (listenfd);
			str_echo(connfd);
			exit(0);
		}

		Close(connfd);
	}
}


