#include "unp.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

void str_echo(int sockfd);


int main(int argc, char **argv)
{
    int listenfd, connfd, udpfd, nready, maxfdp1;
	char mesg[MAXLINE];
	pid_t childpid;
	fd_set rset;
	ssize_t n;
	socklen_t len;
	const int on = 1;
	struct sockaddr_in cliaddr, seraddr;
	void sig_chld(int);

	//create listenning tcp socket
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERV_PORT);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	Bind(listenfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	Listen(listenfd, LISTENQ);

	//create udp socket
	udpfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERV_PORT);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(udpfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	Signal(SIGCHLD, sig_chld);

	FD_ZERO(&rset);

	maxfdp1 = max(listenfd, udpfd) +1;

	for(; ; )
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0)
		{
            if(errno == EINTR)
				continue;                            //back to for
			else
		        fprintf(stderr, "select erro");
		}

		if(FD_ISSET(listenfd, &rset))
		{
			len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &len);

			if((childpid = Fork()) == 0)
			{
				printf("in child\n");
				Close(listenfd);
				str_echo(connfd);
				exit(0);
			}
            
			Close(connfd);
		}
			if(FD_ISSET(udpfd, &rset))
			{
				len = sizeof(cliaddr);
				n = Recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);

				Sendto(udpfd, mesg, n,  0, (struct sockaddr*)&cliaddr, len);
			}
		


	}
}

void sig_chld(int sign)
{
	pid_t pid;
	int stat;

	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("the pid %d termined!\n", pid);

    return ;
}

void str_echo(int sockfd)
{
	ssize_t n;
	
	char recv[MAXLINE];

agin:
	while((n = read(sockfd, recv, MAXLINE)) > 0)
	{
		printf("%s\n",recv);
		Writen(sockfd, recv, n);
	}
	if(n < 0 && errno == EINTR)
		goto agin;
	else if(n < 0)
		fprintf(stderr, "str_erro: read erro");
} 
