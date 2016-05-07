#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (10240)

int do_echo(int sockfd)
{
	char buf[BUFFER_SIZE];
    int  nbytes = 0;

    if ((nbytes = read(sockfd, buf, BUFFER_SIZE)) > 0) {

		write(sockfd, buf, nbytes);
	}

	return nbytes;
}
