#include"unp.h"
void dg_echo(int sockfd,SA *pcliaddr,socklen_t clilen)
{
	printf("0000");
	int n;
	socklen_t len;
	char mesg[MAXLINE];
	char **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;
	char mesg1[10]="error";
	char mesg2[10]="ok";
	for( ; ; )
    {
		 len=clilen;
		 n=Recvfrom(sockfd,mesg,MAXLINE,0,pcliaddr,&len);
		  printf("awrewfdw");
		  mesg[n-1]=0;
		  if((hptr=gethostbyname(mesg))==NULL)
		  {
			   Fputs(mesg1,stdout);
			    snprintf(mesg,sizeof(mesg),"%s\n","error");  
		  }
		  else
		  {
			  printf("111");  
			  Fputs(mesg2,stdout);
			   pptr=hptr->h_addr_list;
			   mesg[0]=0;
			   for( ;*pptr!=NULL;pptr++)	   
		       {
				   strcat(mesg,Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
				   strcat(mesg,"\n");
			   }

           }
		   printf("2222"); 
            Sendto(sockfd,mesg,sizeof(mesg),0,pcliaddr,len);

	}
}
