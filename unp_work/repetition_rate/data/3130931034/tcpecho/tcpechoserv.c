#include "unp.h"
int main (int argc,char **argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	void sig_chld(int);
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(31034);
	bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
	listen(listenfd,LISTENQ);
	signal(SIGCHLD,sig_chld);
	for(;;){
		clilen=sizeof(cliaddr);
		if((connfd=accept(listenfd,(SA*)&cliaddr,&clilen))<0){
			if(errno == EINTR)
				continue;
			else
				err_sys("accept error");
		}	
		if((childpid = fork())==0){
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}	
}
