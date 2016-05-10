#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (1024)

int do_echo(int sockfd)
{
	char buf[BUFFER_SIZE];
    int  nbytes = 0;

    if (nbytes = read(sockfd, buf, BUFFER_SIZE)) {
        if (-1 == nbytes) {
            return -1;
        }

		write(sockfd, buf, strlen(buf));

		return nbytes;
	}

	return 0;
}