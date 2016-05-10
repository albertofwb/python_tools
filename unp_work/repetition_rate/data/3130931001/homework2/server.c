#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 		31001
#define BUF_SIZE	1024

extern int deal_client_request(const char *domain_name, char *respond);

int main (int argc, char *argv[])
{
	char 	buf[BUF_SIZE];
	char    respond[BUF_SIZE];
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	int		udpfd;
	int 	nbytes;
	int 	addrlen = sizeof(struct sockaddr_in);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(31001);
	if((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Server-socket() UDP error!");
		exit(1);
	}
	printf("Server-socket() UDP is OK...\n");
	if(bind(udpfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) {
		perror("Server-bind() EDP error !");
		exit(1);
	}
	printf("%s is listening on PORT:%d\n", argv[0], PORT);
	while(1) {
		memset(buf, 0, sizeof(buf));
		if((nbytes = recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr *) &clientaddr, &addrlen)) <= 0) {
			continue;
		}
		else{
			printf("------------------------\n");
			printf("[UDP][%s:%d] [%d]%s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), nbytes, buf);					
			buf[nbytes] = 0;
			deal_client_request(buf,respond);
			sendto(udpfd, respond, strlen(respond), 0, (struct sockaddr *) &clientaddr, addrlen);
		}
	}
	return 0;
}
