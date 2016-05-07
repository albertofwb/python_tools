#include "unp.h"

int main(int argc,char **argv){
	int sockfd,n;
	struct sockaddr_in sockaddr;
	char recvline[MAXLINE+1];

	if(argc != 2){
		err_quit("usage: a.out<IPaddress>");
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		err_sys("socket eooro");
	}
	
	bzero(&sockaddr,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(31052);

	if(inet_pton(AF_INET,argv[1],&sockaddr.sin_addr) < 0){
		err_sys("inet_pton error");
	}
	
	if(connect(sockfd, (SA *)&sockaddr, sizeof(sockaddr)) < 0){
		err_sys("connect error");
	}

	while((n = read(sockfd,recvline,MAXLINE))>0){
		recvline[n] = 0;
		if(fputs(recvline,stdout) == EOF){
			err_sys("fputs error");
		}
	}

	if(n < 0){
		err_sys("read error");
	}
	exit(0);
}
