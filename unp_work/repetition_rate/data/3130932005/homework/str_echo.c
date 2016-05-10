#include "unp.h"
#include "product.h"

void str_echo(int sockfd)
{
	ssize_t n;
	struct args args;
	struct result result;

	for( ; ;){
		if((n = Readn(sockfd,&args,sizeof(args))) == 0){
			return ;
		}
		result.result = args.arg1 * args.arg2;

		Writen(sockfd,&result,sizeof(result));
	}
}
