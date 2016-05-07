#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/socket.h>
 
#define BUFFER_SIZE 128
#define IP   "101.200.160.104"
#define PORT "31026"
                                                                                                                                                                                             
int main(int argc ,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t peerlen;
	char buf[BUFFER_SIZE];
	struct hostent *ht = NULL ;
	struct in_addr addr;
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		perror("socket");
		exit(-1);
	}
								 
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(PORT));
	servaddr.sin_addr.s_addr = inet_addr(IP);
	if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))  < 0)
	{     
		perror("bind");
		exit(-1);
	}
	printf("bind success \n");
	peerlen = sizeof(cliaddr);
	int i;
	while(1)    
	{
		printf("start\n");
		if(recvfrom(sockfd, buf,sizeof(buf),0,(struct sockaddr *)&cliaddr, &peerlen)< 0)    
		{           
			perror("recvfrom:");    
			exit(-1);       
		}   
		if(strcmp(buf,"quit") == 0) 
			break;      
		ht = gethostbyname(buf);    
		//  printf("gethostbyname:\n");        
		for (i = 0;ht->h_addr_list[i] != NULL;i++ )         
		{                  
			printf("i = %d \n",i);          
			addr.s_addr = (unsigned int *)ht->h_addr_list[i];                 
			printf("IP:%s\n",inet_ntoa(addr));                             
			strcpy(buf,inet_ntoa(addr));       
			sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,peerlen);        
		}   
	}    
	close(sockfd);
	exit(0);
}                 

