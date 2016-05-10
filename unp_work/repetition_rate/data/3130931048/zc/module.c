#include"net.h"
int SetNoBlock(int fd)
{
	int oldopt = fcntl(fd,F_GETFL);
	int newopt = oldopt | O_NONBLOCK;
	fcntl(fd,F_SETFL,newopt);
	return oldopt;
}

bool Add_Event(int epollfd,int fd,bool Et,bool oneshot)
{
	struct epoll_event event ;
	event.data.fd = fd;
	event.events = EPOLLIN;
	if(Et)
	{
		event.events | EPOLLET;
	}	
	if(oneshot)
	{
		event.events | EPOLLONESHOT;
	}
	return !epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}

bool ReOneShot(int epollfd,int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events |EPOLLONESHOT;
	return !epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event); 
}

void* work(void *arg)
{
	int epollfd = ((struct ARG*)arg)->epollfd;
	int listenfd = ((struct ARG*)arg)->listenfd;
	char RECV_BUFF[BUFF_SIZE] = {0};
	while(1)
	{
		int ret = recv(listenfd,RECV_BUFF,BUFF_SIZE-1,0);
		if(ret == 0)
		{
			shutdown(listenfd,SHUT_RDWR);
			printf("cli is out...\n");
			break;
		}
		else if(errno == EAGAIN)
		{
			ReOneShot(epollfd,listenfd);
			printf("read later...\n");
		}
		else
		{
			
			//int num = send(listenfd,"recing cli",100,0);
			printf("get %d from cli \n",strlen(RECV_BUFF));
			
			if(strncmp(RECV_BUFF,"quit",4)== 0)
			{
				printf("this cli id quiting...\n");
				shutdown(listenfd,SHUT_RDWR);
				return NULL;
			}
			int num = send(listenfd,RECV_BUFF,strlen(RECV_BUFF),0);
			printf("%d data have been send \n",num);
			memset(RECV_BUFF,0,BUFF_SIZE);
			
		}
	}
	printf("this thread is outlining...\n");
	return NULL;
}

