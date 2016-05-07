#include "unp.h"
#include <time.h>

int main(int argc,char **argv)
{   
	    int  listenfd,connfd;
		struct sockaddr_in servaddr;   
		char buff[MAXLINE];
        time_t ticks;   //time_t    long int
	    listenfd = Socket(AF_INET,SOCK_STREAM,0);
						    
	    //地址结构初始化
	    bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr =htonl(INADDR_ANY);
		/*访问服务器的多个网卡ip*/
	    servaddr.sin_port = htons(32028);
	    //bind 函数是把本地协议地址赋予一个套接字
		//（本地协议地址：地址与TCP或UDP端口号的结合）
		Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
		//listen函数把一个未连接的套接字转换成被动套接字，指示内核
	    //应该接受指向该套接字的连接请求
		Listen(listenfd,LISTENQ);
		for( ; ; )
	    {
			//accept函数：从已完成的连接队列的对头返回下一个已完成的连接
            connfd = Accept(listenfd,(SA *)NULL,NULL);
			ticks = time(NULL);/*time函数返回1970.1.1以来的秒数*/
		    snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks)); 
	        /*ctime时间转换函数*/   
		    Write(connfd,buff,strlen(buff));
			Close(connfd);
        }
		return 0;
}
