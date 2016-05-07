#include"net.h"
#define IP "101.200.160.104"
#define PORT 31048

int main()
{
	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr(IP);
	saddr.sin_family = 	AF_INET;
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res!=-1);
	res = listen(sockfd,5);
	assert(res!=-1);
	
	int nfds = 100;
	 fd_set rset ,constset;
	FD_ZERO(&constset);
	FD_ZERO(&rset);
	struct timeval time_out = {5,0};

	FD_SET(sockfd,&constset);
			
	char BUFF[1024] = {0};
	printf("will go to while\n");

	while(1)
	{
		rset = constset;
		int count = select(FD_SETSIZE,&rset,NULL,NULL,(struct timeval*)0);
		printf("waiting...count = %d\n",count);
		//printf("")
		if(count == -1)
		{
			perror("select error\n");
			return -1;
		}
		int fd;
		for( fd = 0;fd < count ;++fd)
		{
			if(FD_ISSET(fd,&rset))
			{
				if(fd == sockfd)
				{
					printf("get one connection\n");
					struct sockaddr_in caddr;
					int len = sizeof(caddr);
					int accfd = accept(sockfd,(struct sockaddr*)&caddr,&len);
					assert(accfd!=-1);
					FD_SET(accfd,&constset);
				}
				else
				{
					printf("in else\n");
					recv(fd,BUFF,1023,0);
					send(fd,BUFF,strlen(BUFF),0);
					memset(BUFF,0,1024);
					shutdown(fd,SHUT_RDWR);
				}
			}
		}
	}
	shutdown(sockfd,SHUT_RDWR);
	
	return 0;
}
