#include"unp.h"
int main(int argc,char * *argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socken_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	void sig_chld(int);
	listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(31028);
	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);
	Signal(SIGCHLD,sig-chld);
	for(;;)
	{
		clilen=sizeof(cliaddr);
		if((connfd=accept(listenfd,(SA *)&cliaddr,&clilen))<0)
		{
			if(errno ==  EINIR)
			          continue;
			else
				err_sys("accept error");
		}
		if((childpid=FORK())==0)
		{
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
}
