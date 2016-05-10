#include "unp.h"

int main(int argc,char * * argv)
{
	int listenfd,connfd,udpfd,nready,maxfdp1;
	char mesg[MAXLINE];
	pid_t childpid;
	fd_set rset;
	ssize_t  n;
	socklen_t len;
	const int on = 1;
	struct sockaddr_in cliaddr,servaddr;
	void sig_chld(int);

//建立监听TCP socket
	
	listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32016);					//注意:端口为自己学号的后5位
	
	Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

//建立监听UDP socket

	udpfd = Socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32016);
	Bind(udpfd,(SA *)&servaddr,sizeof(servaddr));

//使用select处理TCP、UDP信号

	Signal(SIGCHLD,sig_chld);
	FD_ZERO(&rset);
	maxfdp1 = max(listenfd,udpfd) + 1;
	for (;;)
	{
		FD_SET(listenfd,&rset);
		FD_SET(udpfd,&rset);
		if ((nready = select(maxfdp1,&rset,NULL,NULL,NULL))<0)
		{
			if (errno == EINTR)
				continue;
			else
				err_sys("select error");
		}
		if (FD_ISSET(listenfd,&rset))
		{
			len = sizeof(cliaddr);
			connfd = Accept(listenfd,(SA *)&cliaddr,&len);
			if ((childpid = Fork())== 0)
			{
				Close(listenfd);
				str_echo(connfd);
				exit(0);
			}
			Close(connfd);
		}
	}
		if (FD_ISSET(udpfd,&rset))
		{
			len = sizeof(cliaddr);
			n = Recvfrom(udpfd,mesg,MAXLINE,0,(SA *)&cliaddr,len);
			printf("%s\n", mesg);
			Sendto(udpfd,mesg,n,0,(SA *)&cliaddr,len);
		}
}
