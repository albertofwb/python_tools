#include "unp.h"

int
main(int argc, char **argv)
{
	int		sockfd;
	struct	sockaddr_in servaddr,cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM,0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family	=	AF_INET;
	servaddr.sin_addr.s_addr =htonl(INADDR_ANY);
	servaddr.sin_port =htons(31040);

	Bind(sockfd,(SA *)&servaddr, sizeof(servaddr));

	printf("%d\n",sockfd);
	dg_echo(sockfd, (SA *) &cliaddr,sizeof(cliaddr));
}	

