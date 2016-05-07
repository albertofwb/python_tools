#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "pollfd_mgr.h"


/* Return Value:
 *        On success, 0 is returned;
 *        On failure, -1 is returned;
 *        No events, 1 is returned.
 */

int 
handle_listen(struct pollfd * pollfds, size_t len, int index)
{
    int                 cli_fd = -1                  ;
	struct sockaddr_in  cliaddr                      ;
	socklen_t           cliaddr_len = sizeof(cliaddr);

    // POLLIN or POLLPRI
	if ( pollfds[index].revents & (POLLIN | POLLPRI)) {

		if (0 <= (cli_fd = accept(pollfds[index].fd, (struct sockaddr *)&cliaddr, &cliaddr_len))) {
            
			int tmp_idx = pollfd_set(pollfds, len, cli_fd);
			
			if (-1 == tmp_idx) {
    		    printf("[ Errors ] serve for %s failed\n", inet_ntoa(cliaddr.sin_addr));
				close(cli_fd);
				return -1;
			}
			else {
			    pollfds[tmp_idx].events  = POLLIN | POLLPRI;
				pollfds[tmp_idx].revents = 0; 
			}
		}
		else {
    	     perror("[ Errors ] ");
		     return -1;
		}
	    
		printf("[ Login  ] endpoint: %s:%d on fd[%d] online\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), cli_fd);
	
        pollfds[index].revents = 0;

		return 0;
	}
	// POLLERR
	else if (pollfds[index].revents & POLLERR) {
        perror("[ Errors ] ");
		return -1;
    }

    return 1;
}
