#include "unp.h"
//#include <time.h>
int
main(int argc,char **argv)
{
	  int listenfd,connfd;
	  struct sockaddr_in servaddr;
	  long m,n;
	  char line[MAXLINE];
		listenfd = Socket(AF_INET,SOCK_STREAM,0);
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		servaddr.sin_port =htons(31029);
		Bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
		Listen(listenfd,LISTENQ);
		for(;;){
		         connfd=Accept(listenfd,(SA*)NULL,NULL);
					Readline(connfd,line,MAXLINE);
				    if(sscanf(line,"%ld %ld",&m,&n)==2)
						{
							printf("1.%ld,%ld\n",m,n);																												            snprintf(line,sizeof(line),"%ld\n",m*n);
							printf("2.%ld\n",m*n);
							printf("3. %s\n",line);
							Writen(connfd,line,strlen(line));}
				    else
						printf("cuowu");
			Close(connfd);
				}
}

