#include "unp.h"
void
dg_echo(int sockfd,SA *pcliaddr,socklen_t clilen){
	int n;
	socklen_t len;
	struct hostent *hptr;
	char **pptr;
	char str[INET_ADDRSTRLEN];
	char mesg[MAXLINE];
	for(;;){
		len = clilen;
		n = Recvfrom(sockfd,mesg,MAXLINE,0,pcliaddr,&len);
		mesg[n -1] = '\0';
		if((hptr = gethostbyname(mesg))==NULL){
			snprintf(mesg,sizeof(mesg),"%s\n","error");
		
		}else{
			pptr = hptr->h_addr_list;
			mesg[0] = 0;
			for(;*pptr != NULL;pptr++){
				strcat(mesg,Inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
				strcat(mesg,"\n");
			}
		
		}
		Sendto(sockfd,mesg,n,0,pcliaddr,len);
	}

}
