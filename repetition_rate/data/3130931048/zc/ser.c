#include"net.h"
#define IP "101.200.160.104"
#define PORT 31048
#define MAX_NUM_EVENT 1024
int main()
{	
	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr(IP);
	
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd != -1);

	int res = bind(listenfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res!=-1);
	
	res = listen(listenfd,5);
	assert(res!=-1);

	struct epoll_event events[MAX_NUM_EVENT];
	int epoll_fd = epoll_create(128);
	Add_Event(epoll_fd,listenfd,false,false);
	
	while(1)
	{
		int ret = epoll_wait(epoll_fd,events,MAX_NUM_EVENT,-1);
		if(ret < 0)
		{
			perror("epoll_wait error \n");
			break;
		}
		else
		{
		//	int dealfd;
			for(int i = 0;i<ret ;++i)
			{
				//dealfd = events[i].data.fd;
				if(events[i].data.fd == listenfd)
				{
					struct sockaddr_in caddr;
					socklen_t len = sizeof(caddr);
					int clifd = accept(events[i].data.fd,(struct sockaddr*)&caddr,&len);
					assert(clifd!=-1);
					printf("accept ok\n");
					Add_Event(epoll_fd,clifd,true,true);
				}
				else if(events[i].events & EPOLLIN)
				{
					pthread_t thread;
					struct ARG arg;
					arg.listenfd = events[i].data.fd;
					arg.epollfd = epoll_fd;
					pthread_create(&thread,NULL,work,(void *)&arg);	
				}
				else
				{
					printf("unknown thing happened\n");
				}
			}
		}
	}
	close(listenfd);
	
	return 0;
}
