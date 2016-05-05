#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
#define BUFF_SIZE 1024
struct ARG
{
	int epollfd;
	int listenfd;
};
bool Add_Event(int epollfd,int fd,bool Et,bool oneshot);
int SetNoBlock(int fd);
bool Reoneshot(int fd);
void* work(void *arg);

