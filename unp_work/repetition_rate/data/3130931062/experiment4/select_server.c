#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/select.h>

#include "common_linklist/jlinklist.h"

#define LISTEN_Q    (10)
#define LISTEN_PORT (31062)
#define FD_SIZE     (256)


Boolean match(void * data, void * key)
{
    if (*((int *)key) == *((int *)data)) {
		return TRUE;
	}

	return FALSE;
}

int         runing = 1;
link_list_T fds_list;

int main(int argc, char *argv[])
{
	int   listen_fd = -1;
	int   cli_fd    = -1;

	struct sockaddr    cliaddr;
	socklen_t          cliaddr_len;

	struct sockaddr_in addr;
	socklen_t          addr_len = sizeof(addr);

	addr.sin_family       = AF_INET;
	addr.sin_addr.s_addr  = inet_addr("0.0.0.0"); // INADDR_ANY -> 0
	addr.sin_port         = htons(LISTEN_PORT);

	if (-1 == (listen_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		goto Err1;
	}

	if (-1 == bind(listen_fd, (struct sockaddr*)&addr, addr_len)) {
		goto Err2;
	}

    if (-1 == listen(listen_fd, LISTEN_Q)) {
		goto Err2;
	}

	fd_set rset;
	FD_ZERO(&rset);
	
	init_list(&fds_list);

	while ( runing ) {
		memset(&cliaddr, 0, sizeof(cliaddr));
		
		printf("[ Inform ] selecting...\n");

		//---- reinstall fds
		int   i   = get_list_length(&fds_list);
		int * ptr = NULL;
		FD_ZERO(&rset);
		FD_SET(listen_fd, &rset);
		for (; i ; --i) {
			ptr = (int*)get_node_data_by_num(&fds_list, i);
			if ( ptr ) {
			    FD_SET(*(ptr), &rset);
		    }
			else {
				fprintf(stderr, "[ Errors ] FD_SET error\n");
			}
		}

		//---- select
		if (-1 == select(FD_SIZE, &rset, NULL, NULL, NULL)) {
			perror("[ Errors ] ");
			continue;
		}

		//---- check if listen_fd has event
		if (FD_ISSET(listen_fd, &rset) && (cli_fd = accept(listen_fd, &cliaddr, &cliaddr_len))) {
			//printf("[ Inform ] a new endpoint: %s:%d\n", inet_ntoa(((struct sockaddr_in *)&cliaddr)->sin_addr.s_addr), ntohs(((struct sockaddr_in)cliaddr).sin_port));
			printf("[ Inform ] listen_fd event\n");
			printf("[ Inform ] new client -> fd[%d]\n", cli_fd);
			push_back(&fds_list, &cli_fd, sizeof(cli_fd));
		}
		else if (-1 == cli_fd) {
			perror("[ Errors ] ");
			continue;
		}
		
		//---- check if other fds have event
        for (i = 0; i < FD_SIZE; ++i) {
			if (FD_ISSET(i, &rset) && i != listen_fd) {
				printf("[ Inform ] fd[%d] event\n", i);
				int rst = do_echo(i);
				if (-1 == rst) {
				    printf("[ Inform ] fd[%d] read return -1\n", i);
					pop_node(&fds_list, NULL, match, &i);
				}
				else if (0 == rst) {
				    printf("[ Inform ] fd[%d] read return 0\n", i);
					pop_node(&fds_list, NULL, match, &i);
				}
			}
		}
	}

	close(listen_fd);
	destroy_list(&fds_list);

	exit(EXIT_SUCCESS);

Err2:
	close(listen_fd);
Err1:
	perror("[ Errors ] ");
	exit(EXIT_FAILURE);
}
