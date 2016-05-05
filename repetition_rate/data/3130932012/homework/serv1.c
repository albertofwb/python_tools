#include "unp.h"
#include "pro.h"
void str_echo(int sockfd)
{
	ssize_t   n;
	struct args  args;
	struct result result;

	for(;;)
	{
		if((n==Read(sockfd,&args,sizeof(args))))
				return;
		result.pro=args.arg1*args.arg2;
		Writen(sockfd,&result,sizeof(result));
	}
}
