#include "unp.h"

void sig_chld(int signo){
	 pid_t pid;
	 int stat;
     while((pid = waitpid(-1,&stat,WNOHANG))>0)
		 printf("child %d terminated\n",pid);
	 return;
}

void str_echo(int sockfd){
	  ssize_t n;
	  char buf[MAXLINE];
 again:
      while((n = read(sockfd,buf,MAXLINE) )>0)
		  Writen(sockfd,buf,n);
      if(n<0 && errno == EINTR )
          goto again;
	  else if(n<0)
		  err_sys("str_echo:read error ");
}

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t chilen;
	struct sockaddr_in cliaddr,servaddr;
	void sig_chld(int);

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32028);

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);
	                                                                                
	Signal (SIGCHLD,sig_chld);

	for(;;){
        chilen = sizeof(cliaddr);
	    if((connfd = accept(listenfd,(SA *)&cliaddr,&chilen))<0)
	    {
	        if(errno == EINTR) 
   	             continue;
 
			else 
		         err_sys("accpet error");

	    }
		if ((childpid = Fork())== 0)
		{
			Close(listenfd);
		    str_echo(connfd);
			exit(0);
        }          
		Close(connfd);
    }
}   
