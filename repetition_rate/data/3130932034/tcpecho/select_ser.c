#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXFD 10

void fds_int(int*fds)
{
	int i = 0;
	for(;i<MAXFD;++i)
	{
		fds[i] = -1;
	}
}

void fds_add(int fd,int *fds)
{
	int i = 0;
	for(;i<MAXFD;++i)
	{
		if(fds[i] == -1)
		{
			fds[i] = fd;
			break;
		}
	}
}

void fds_del(int fd,int *fds)
{
	int i = 0;
	for(;i<MAXFD;++i)
	{
		if(fds[i] == fd)
		{
			fds[i] = -1;
			break;
		}
	}
}

int main()
{
	int fds[MAXFD];
	fds_int(fds);
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr,caddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(32034);
	saddr.sin_addr.s_addr = inet_addr("101.200.160.104");
	
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(res == -1)
	{
		perror("bind error");
	}

	listen(sockfd,5);

	fd_set fdset;
	fds_add(sockfd,fds);

	while(1)
	{
		FD_ZERO(&fdset);
		int maxfd = -1;

		int i = 0;
		for(;i<MAXFD;++i)
		{
			if(fds[i] != -1)
			{
				FD_SET(fds[i],&fdset);
				if(fds[i] > maxfd)
				{
					maxfd = fds[i];
				}
			}
		}

		struct timeval tv = {10};
		int n = select(maxfd+1,&fdset,NULL,NULL,&tv);
		if(n == -1)
		{
			perror("select error");
			continue;
		}
		else if (n == 0)
		{
			printf("time out\n");
			continue;
		}
		else
		{
			int j  =0;
			for(;j<MAXFD;++j)
			{
				if(fds[j] == -1)
				{
					continue;
				}

				if(FD_ISSET(fds[j],&fdset))
				{
					if(fds[j] == sockfd)
					{
						int len = sizeof(caddr);
						int connfd = accept(sockfd,(struct sockaddr*)&caddr,&len);
						if(connfd == -1)
						{
							continue;
						}

						printf("port:%d,connfd=%d\n",ntohs(caddr.sin_port),connfd);
						fds_add(connfd,fds);
					}
				    else
				    {
				   		char buff[128] = {0};
						int m = recv(fds[j],buff,127,0);
						if(m <= 0)
						{
							close(fds[j]);
							fds_del(fds[j],fds);

							printf("one client over\n");
						}
						else
						{
							printf("buff = %s\n",buff);
							send(fds[j],"ok",2,0);
						}
					}
				}
			}
		}
	}
}

