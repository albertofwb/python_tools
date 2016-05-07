#include "unp.h"

void sig_chld(int signo)
{
    pid_t pid;
	int stat;

	while((pid = waitpid(-1,&stat,WNOHANG))>0)
         printf("child %d terminated\n",pid);
	return;
}

void str_echo(int sockfd){
	long a,b;
    ssize_t n; 
	char buf[MAXLINE];
	for(;;)
	{
		if((n = Readline(sockfd,buf,MAXLINE)) == 0)
			return;
		if(sscanf(buf,"%ld%ld",&a,&b) == 2)
			snprintf(buf,sizeof(buf),"%ld\n",a+b);
		else 
			snprintf(buf,sizeof(buf),"input error\n");

		n = strlen(buf);
		Writen(sockfd,buf,n);
	
	}
}

int main(int argc,char **argv)
{
	//变量声明
    int listenfd,connfd;                  //监听套接字，链接套接字
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;  //套接口结构体
    void    sig_chld(int);

	//变量初始化
	listenfd = Socket(AF_INET,SOCK_STREAM,0);
        //套接口地址结构体初始化四步
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;                      //协议族
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   //网卡ip
	servaddr.sin_port = htons(32028);                   //绑定端口

	//绑定套接口
    Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);  
	/*将一个未连接的套接字转换为被动套接字只是内核应接受指向该套接字的连接请求*/
    Signal(SIGCHLD,sig_chld);
	for  ( ; ; )
	{
		clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd,(SA *)&cliaddr,&clilen)) < 0)
		{
		    if(errno == EINTR)
				continue;
			else
				err_sys("accept error");
		}
       if((childpid = Fork()) == 0){
	       Close(listenfd);
		   str_echo(connfd);
		   exit(0);
	   }
	   Close(connfd);
	}
}

