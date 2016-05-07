#include "unp.h"

void dg_echo(int sockfd,SA * pcliaddr,socklen_t clilen)
{

	int n;
	socklen_t len;
	char msg[MAXLINE];
	struct hostent *hptr;
	char **pptr;
	char  str[INET_ADDRSTRLEN];
	while(1)
	{
		len =clilen;

		n= Recvfrom (sockfd,msg,MAXLINE,0,pcliaddr,&len);
		msg[n-1]=0;

		if (NULL ==(hptr=gethostbyname(msg))){
			snprintf(msg,sizeof(msg),"%s\n","error");

		}
		else
		{
			pptr = hptr->h_addr_list;
			msg[0]=0;
			for (;*pptr !=NULL;pptr++)
			{
				strcat (msg,Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
				strcat(msg,"\n");
			}
		}
		Sendto(sockfd,msg,sizeof(msg),0,pcliaddr,len);
	}
}
