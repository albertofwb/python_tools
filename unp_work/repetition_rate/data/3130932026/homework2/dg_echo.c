#include "unp.h"
void 
dg_echo(int sockfd,SA *pcliaddr,socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[MAXLINE];
	struct hostent *hptr;
	char **pptr;
	char str[INET_ADDRSTRLEN];

	for( ; ; )
	{
		len = clilen;
		n=Recvfrom(sockfd,mesg,MAXLINE,0,pcliaddr,&len);
		mesg[n-1] = 0;
		if((hptr = gethostbyname(mesg)) == NULL)
		{
			snprintf(mesg,sizeof(mesg),"%s\n","error");

		}
		else
		{
			pptr = hptr->h_addr_list;
			mesg[0]=0;
			for( ;*pptr != NULL;pptr++)
			{
				strcat(mesg,Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
				strcat(mesg,"\n");
			}
			printf("official hostname: %s\n",hptr->h_name);

			for(pptr = hptr->h_aliases;*pptr != NULL;pptr++)
			{
				printf("\talias: %s\n",*pptr);
			}
			
			switch (hptr->h_addrtype)
			{
				case AF_INET:
#ifdef AF_INET6
				case AF_INET6:
#endif
					pptr = hptr->h_addr_list;
					for( ;*pptr != NULL;pptr++)
						printf("\taddress:%s\n",Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
					break;
				default:
					err_ret("unknown address type");
					break;
			}
		}
	}
	exit(0);
}
