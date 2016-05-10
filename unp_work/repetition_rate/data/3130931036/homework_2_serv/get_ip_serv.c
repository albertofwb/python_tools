#include "unp.h"
#define MY_SERV_PORT (31036)

int main(int argc, char **argv)
{
	int    sockfd              ;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr ;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family      = AF_INET            ;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY)  ;
	servaddr.sin_port        = htons(MY_SERV_PORT);

	Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

	ip_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
