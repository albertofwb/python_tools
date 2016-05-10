#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#include "pollfd_mgr.h"

//---- handle read events
int 
handle_events(struct pollfd * pollfds, size_t len, size_t nevents) {
	
	int i = 0;

	for (i = 0; i < len && nevents > 0; ++i) {
		
		int retval = 0;
		
		if (-1 != pollfds[i].fd && 
			 0 != pollfds[i].revents && 
			 i != 0) {
			
			--nevents;
	        
			// POLLIN or POLLPRI
		    if (pollfds[i].revents & (POLLIN | POLLPRI)) {
		    	
				retval = do_echo(pollfds[i].fd);
				
				if (-1 == retval) {
					fprintf(stderr, "[ Errors ] error on fd[%d] ->", pollfds[i].fd);
	        	    perror(" ");
	
					close(pollfds[i].fd);
	        	    pollfds[i].fd = -1;
				}
				else if (0 == retval){
	        	    printf("[ Logout ] fd[%d] released\n", pollfds[i].fd);
	
					close(pollfds[i].fd);
	        	    pollfds[i].fd = -1;
				}
			}
	        // POLLRDHUP
			else if (pollfds[i].revents & POLLRDHUP) {
	            fprintf(stderr, "[ Logout ] endpoint on fd[%d] offline\n", pollfds[i].fd);
	
				close(pollfds[i].fd);
				pollfds[i].fd = -1;
			}
	
			// clear revevts
	        pollfds[i].revents = 0;
		}
	}

	return 0;
}
