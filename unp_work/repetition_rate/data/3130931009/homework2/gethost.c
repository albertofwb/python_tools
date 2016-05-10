#include	"unp.h"
char *
gethost(char *name)
{	char *msg=name;
				char **pptr;
				struct hostent	*hptr;
				int i=0;
				struct sockaddr_in addr;
				char *address="Ip address is ";
					if ( (hptr = gethostbyname(name)) == NULL)
	//							return "error";
					for (pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
							{
				char *tmp= pptr[i++];
				strcpy(msg,address);
							}
											
					
								//			return(msg);
	return name;
}
