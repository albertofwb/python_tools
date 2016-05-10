#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../conn/conn.h"

#define BUFFER_SIZE (102400)

int cli_runing = 1;

int do_fork(int sockfd)
{
	char buf[BUFFER_SIZE];
    int  nbytes = 0;

    while ( cli_runing ) {
        if (nbytes = read(sockfd, buf, BUFFER_SIZE)) {
            if (-1 == nbytes) {
				close(sockfd);
                return 1;
            }
            
			if (0 == nbytes) {
				break;
			}

			write(sockfd, buf, nbytes);
        	
			if ( !strcmp("quit", buf) ) {
				cli_runing = 0;
			}
		}
    }

	close(sockfd);
	return 0;
}
