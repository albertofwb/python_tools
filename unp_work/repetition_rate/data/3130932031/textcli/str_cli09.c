#include "unp.h"
struct args
{
	long arg1;
	long arg2;
};
struct result
{
	long sum;
};

void str_cli(FILE *fp,int sockfd)
{
	char sendline[MAXLINE];
	struct args args;
	struct result result;
	while(Fgets(sendline,MAXLINE,fp)!=NULL)
	{
		if(sscanf(sendline,"%ld%ld",&args.arg1,&args.arg2)!=2)
		{
			printf("invalid input:%s",sendline);
			continue;
		}
		else
		{
		    Writen(sockfd,&args,sizeof(args));
		    if(Readn(sockfd,&result,sizeof(result))==0)
			   err_quit("str_cli:server terminated prematurely");
			else
		       printf("%ld\n",result.sum);
	}
}
