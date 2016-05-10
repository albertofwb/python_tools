#include "unp.h"

void dg_echo(int udpfd,SA* pcliaddr,socklen_t clilen)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];

	struct hostent *hptr;
    char **pptr;
	char str[INET_ADDRSTRLEN];
   
    for(; ;)
    {
        len = clilen;
        n = Recvfrom(udpfd,mesg,MAXLINE,0,pcliaddr,&len);
        mesg[n - 1] = 0; 
        
		if((hptr = gethostbyname(mesg)) == NULL)
		{
		    snprintf(mesg,sizeof(mesg),"%s\n","error");
		}else{
			pptr = hptr->h_addr_list;
			mesg[0]=0;
			for(;*pptr != NULL;pptr++)
			{
		        strcat(mesg,Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
				strcat(mesg,"\n");
			}

     		sendto(udpfd,mesg,sizeof(mesg),0,pcliaddr,len);
		}
    }
}

int main(int argc,char ** argv)
{
    int udpfd;
	struct sockaddr_in cliaddr ,servaddr;

    udpfd = Socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32028);

	Bind(udpfd,(SA*)&servaddr,sizeof(servaddr));

	dg_echo(udpfd,(SA*)&cliaddr,sizeof(cliaddr));
    return 0;
}
