///////////////////////////////////////////////////////////////
//
//homework1:
//	get 2 number(divided by ',') from cli to add ,send the result to the cli.
//	
//	product from zhangcong 3130931048 
//
///////////////////////////////////////////////////////////////
#include"net.h"
#define IP "101.200.160.104"
#define PORT 31048 
static int count = 1;
int setnoblock(int fd)
{
	assert(fd >0);
	int oldopt = fcntl(fd,F_GETFD,NULL);
	int newopt = oldopt | O_NONBLOCK;
	fcntl(fd,F_SETFD,&newopt);
	return oldopt;
}
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
	int one = 1;
	socklen_t lenone = sizeof(one);
	assert(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(void*)&one,lenone)!=-1);
	FD_SET(sockfd,&cset);
	int ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(ret!=-1);

	ret = listen(sockfd,5);
	assert(ret!=-1);

	char buff[1024] = {0};

	while(1)
	{
		rset = cset;
		ret = select(1024,&rset,NULL,NULL,&timeout);
		if(ret == -1)
		{
			perror("select error\n");
		}
		int i = 0;
		for(;i<1024 ;++i)
		{
			if(FD_ISSET(sockfd,&rset))
			{

				if(i == sockfd)
				{
					int connfd = accept(sockfd,(struct sockaddr*)&caddr,&len);
					connfd==-1?perror("connfd == -1"):NULL;
					printf("accept ok\n");
					FD_SET(connfd,&cset);
					setnoblock(connfd);
					continue;
			
				}
				else 
				{
					int ret = recv(i,buff,1023,0);
					if(ret == 0)
					{
						FD_CLR(i,&cset);
						close(i);
					}
					else if(ret > 0)
					{
						char sendbuff[64] = {0};
						printf("%s",buff);
						int a ;
						int b ;
						//get two num
						sscanf(buff,"%d,%d",&a,&b);
						
						printf("%d + %d = %d\n",a,b,a+b);
						sprintf(sendbuff,"%d + %d = %d\n",a,b,a+b);
						send(i,sendbuff,strlen(sendbuff),0);
						memset(buff,0,1024);
						memset(sendbuff,0,64);
					}
				}
			}
			else
			{

			}
		}
	}
}
