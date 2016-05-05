#include"net.h"
#define IP "101.200.160.104"
#define PORT 31048 
static int count = 1;
int main()
{
	struct sockaddr_in saddr,caddr;
	memset(&saddr,0,sizeof(saddr));
	memset(&saddr,0,sizeof(caddr));
	int len = sizeof(caddr);

	 fd_set cset,rset;
	struct timeval timeout = {5,0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr(IP);

	FD_ZERO(&cset);
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);
	FD_SET(sockfd,&cset);
	int ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(ret!=-1);

	ret = listen(sockfd,5);
	assert(ret!=-1);

	char buff[1024] = {0};

	while(1)
	{
		rset = cset;
		//printf("%d\n",count++);
		ret = select(1024,&rset,NULL,NULL,&timeout);
		printf("ret  is %d\n",ret);
		if(ret == -1)
		{
			perror("select error\n");
		}
		int i = 0;
		for(;i<ret ;++i)
		{
			printf("i = %d\n",i);
			if(FD_ISSET(i,&rset))
			{

				if(i == sockfd)
				{
					int connfd = accept(sockfd,(struct sockaddr*)&caddr,&len);
					connfd==-1?perror("connfd == -1"):NULL;
					printf("accept ok\n");
					FD_SET(connfd,&cset);
					continue;
			
				}
				else 
				{
					int ret = recv(sockfd,buff,1023,0);
					if(ret == 0)
					{
						FD_CLR(i,&cset);
						close(i);
					}
					else if(ret > 0)
					{
						printf("%s",buff);
						memset(buff,0,1024);
					}
					else
					{
						printf("recv error\n");
					}
				}
			}
			else
			{

			}
		}
	}
}
