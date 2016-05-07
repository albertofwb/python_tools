#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <poll.h>

#include "conf.h"

#include "pollfd_mgr.h"
int handle_events(struct pollfd * pollfds, size_t len, size_t nevents);

int          runing = 1;

int main(int argc, char *argv[])
{
	struct pollfd pollfds[FD_SIZE];

	if ( init_pollfd_set(pollfds, FD_SIZE) ) {
		goto Err0;
	}

	int   listen_fd  = -1;
	int   listen_idx = -1;

	struct sockaddr_in addr;
	socklen_t          addr_len = sizeof(addr);

	addr.sin_family       = AF_INET;
	addr.sin_addr.s_addr  = inet_addr("0.0.0.0"); // INADDR_ANY -> 0
	addr.sin_port         = htons(LISTEN_PORT);

	//---- invoke socket system call
	if (-1 == (listen_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		goto Err1;
	}
    //---- invoke bind
	if (-1 == bind(listen_fd, (struct sockaddr*)&addr, addr_len)) {
		goto Err2;
	}
    //---- invoke listen
    if (-1 == listen(listen_fd, LISTEN_Q)) {
		goto Err2;
	}
	//---- initialize pollfd set
	if (-1 == (listen_idx = pollfd_set(pollfds, FD_SIZE, listen_fd)) ) {
		goto Err0;
	}


	//---- add listen_fd into pollfd set
	pollfds[listen_idx].events = POLLIN | POLLPRI;
    
	//---- main loop
	while ( runing ) {
		
		printf("[ Inform ] will invoke poll ......\n");
	
		//---- invoke poll
		int nevents = 0;
		if (-1 == (nevents = poll(pollfds, FD_SIZE, -1))) {
			perror("[ Errors ] ");
			continue;
		}

        printf("[ Inform ] poll found %d events\n", nevents);
		
		//---- handle events of the listen_fd
        handle_listen(pollfds, FD_SIZE, listen_idx);
		
        //---- handle read events    
		handle_events(pollfds, FD_SIZE, nevents);
	} 

	close(listen_fd);

	exit(EXIT_SUCCESS);

Err2:
	close(listen_fd);
Err1:
	perror("[ Errors ] ");
Err0:
	exit(EXIT_FAILURE);
}
