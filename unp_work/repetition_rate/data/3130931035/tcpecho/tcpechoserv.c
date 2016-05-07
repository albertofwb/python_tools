#include "unp.h"
int main(int argc,char**argv)
{
    int listenfd,connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;
    void sig_chld(int);
    listenfd=Socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;

    servaddr.sin_addr.s_addr=htons(INADDR_ANY);
    servaddr.sin_port=htons(31035);
    Bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
   
    Listen(listenfd,LISTENQ);
    Signal(SIGCHLD,sig_chld);
    for(;;)
    {
	clilen=sizeof(cliaddr);
	if((connfd=Accept(listenfd,(SA*)&cliaddr,&clilen))<0)
	{
	    if(errno==EINTR)
		continue;
	    else
		err_sys("accept error");
	}
	if((childpid=Fork())==0)
	{
	    Close(listenfd);
	    str_echo(connfd);
	    exit(0);
	}

	Close(connfd);
    }
}
