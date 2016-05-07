#include"net.h"
void SendToCli_Ip(char *str,int fd)
{
	assert(str!=NULL);
	printf("getfrom ser :%s\n",str);
//flag :
	struct hostent *hptr = gethostbyname(str);
	if(hptr == NULL)
	{
		switch(h_errno)
		{
			case HOST_NOT_FOUND:
				printf("this host is not found\n");
				break;
			case TRY_AGAIN:
				printf("try again\n");
//				goto flag;
			case NO_RECOVERY:
				printf("no_recovery\n");
				break;
			case NO_DATA:
				printf("no data \n");
			default :
				printf("unkonw error\n");
				break;
		}
	}
	else
	{
		printf("the official name is : %s\n",hptr->h_name);
		if(hptr->h_addrtype == AF_INET)
		{
			char buff[128]= {0};
			int count = 0;
			char **pptr = hptr->h_addr_list;
			while(*pptr!=NULL)
			{
		
				char *ip = inet_ntop(hptr->h_addrtype,*pptr,buff,INET_ADDRSTRLEN);
				printf("addr is : %s\n",ip);
			
				int ret = send(fd,ip,strlen(ip),0);
				printf("send to cli %d byte\n",ret);
				//memset(buff,0,128);
				++pptr;
			}
		}
	}
}
/*
int main()
{
	char *str = "www.sina.com";
	char buff[128] = {0};
	fgets(buff,127,stdin);
	buff[strlen(buff)-1]= 0;
	ShowIp(buff);
	return 0;
}*/
