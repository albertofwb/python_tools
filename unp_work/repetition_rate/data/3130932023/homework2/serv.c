#include "unp.h"


void dg_echo(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen);
static void recvfrom_int(int);
static int count;

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in seraddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM,0);

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERV_PORT);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

	dg_echo(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

}

void dg_echo(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen)
{
	int n;
    socklen_t len;
	char HostName[MAXLINE];
    struct hostent *host;
    struct in_addr addr;
	char *buff;

	Signal(SIGINT, recvfrom_int);
  
	n = 220 * 1024;
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));

    for(;;)
	{
        len = clilen;
		bzero(HostName, sizeof(HostName));
	    Recvfrom(sockfd, HostName, MAXLINE, 0, pcliaddr, &len);          //get the hostname frome the client 

		count++;

		
		/*next we need to use the hostname to get the ip address and sent it to the client*/
        host = gethostbyname(HostName);
		printf("Hostname=<%s>\n", HostName);
		if(host == NULL)
		{
			//printf("gethostbyname error!:%d\n", errno);
			 switch (h_errno)  
		     {  
	          case HOST_NOT_FOUND:
			      fputs ("The host was not found.\n", stderr);  
	              break;  
	          case NO_ADDRESS:  
	              fputs ("The name is valid but it has no address.\n", stderr);  
	              break;  
	          case NO_RECOVERY:  
	              fputs ("A non-recoverable name server error occurred.\n", stderr);  
	              break;  
	          case TRY_AGAIN: 
				  fputs ("The name server is temporarily unavailable.", stderr);  
                 break;  

			 }
        }
        
		addr.s_addr = *(unsigned long * )host->h_addr;
		buff = inet_ntoa(addr);
		printf("%s\n", buff);
	    Sendto(sockfd, buff, strlen(buff), 0, pcliaddr, len);                          //sent the host message to the client
       
	}
}


static void recvfrom_int(int signo)
{
     printf("\nrecieved %d datagram\n", count);
	 exit(0);
}


