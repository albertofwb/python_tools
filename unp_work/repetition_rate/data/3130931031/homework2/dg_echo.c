#include "unp.h"
#include<string.h>
void
dg_echo(int sockfd,SA *pcliaddr,socklen_t clilen)
{
     int n;
	 socklen_t len;
	 char mesg[MAXLINE];
	 struct hostent *hptr;
	 char **pptr;
	 char str[INET_ADDRSTRLEN];
	 for(;;)
	     {
	          len=clilen;
	          n=Recvfrom(sockfd,mesg,MAXLINE,0,pcliaddr,&len);
	          mesg[n-1]='\0';
	          hptr=gethostbyname(mesg);
	          pptr=hptr->h_addr_list;
	          mesg[0]=0;
	          for(;*pptr!=NULL;pptr++)
	             {
             		  strcat(mesg,Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
					  strcat(mesg,"\n");
	             }
 	         Sendto(sockfd,mesg,strlen(mesg),0,pcliaddr,len);
	     }
}
