#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* port we're listening on */
#define PORT 		31057
#define BUF_SIZE	1024

extern int deal_client_request(const char *domain_name, char *respond);

int main (int argc, char *argv[])
{
#if 0 
    char 	buf[BUF_SIZE] = "www.sohu.com";
    char    respond[BUF_SIZE];
    deal_client_request(buf, respond);
    fputs(respond, stdout);
#else
    char 	buf[BUF_SIZE];
    char    respond[BUF_SIZE];
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
	int		udpfd;
    int 	nbytes;
    int 	addrlen = sizeof(struct sockaddr_in);

    /* bind */
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);


    if((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Server-socket() UDP error!");
        exit(1);
    }

	if(bind(udpfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) {
        perror("Server-bind() EDP error !");
        exit(1);
	}
    /* loop */
    while(1) {
        memset(buf, 0, sizeof(buf));
        if((nbytes = recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr *) &clientaddr, &addrlen)) <= 0) {
            continue;
        }else{
            // del '\n'
            buf[nbytes] = 0;
            //strcpy(buf, "www.baidu.com");
            deal_client_request(buf, respond);
            //fputs(respond, stdout);
            sendto(udpfd, respond, strlen(respond), 0, (struct sockaddr *) &clientaddr, addrlen);
            //sendto(udpfd, buf, nbytes, 0, (struct sockaddr *) &clientaddr, addrlen);
        }
    }// while(1) loop
#endif
    return 0;
}
