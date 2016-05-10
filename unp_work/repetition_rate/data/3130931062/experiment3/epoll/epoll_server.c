#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/epoll.h>

#include "../../color/ansi_color.h"

#define SERV_PORT (31062)
#define LISTEN_Q  (16)

#define EPOLL_SIZE (16)

#define SERV_RUN  (1)
#define SERV_ERR  (2)
#define SERV_EXIT (0)

int serv_runing = SERV_RUN;

int main(int argc, char * argv[])
{
	struct epoll_event   events[EPOLL_SIZE]         ;
	struct epoll_event   ev                         ;
	int                  listen_fd, tmp_fd, epoll_fd;

    struct sockaddr_in   addr                       ;
	socklen_t            addr_len = sizeof addr     ;

    struct sockaddr_in   cli_addr                   ;
	socklen_t            cli_addr_len = sizeof cli_addr;

	//---- epoll_create
	if ( -1 == (epoll_fd = epoll_create(EPOLL_SIZE)) ) {
		fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
		perror(" epoll_create");
	    exit(EXIT_FAILURE);
	}

	//---- socket
    if (-1 == (listen_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
		perror(" socket");
		exit(EXIT_FAILURE);
	}

	//---- configure sockaddr
	addr.sin_family       =  AF_INET;
	addr.sin_addr.s_addr  =  inet_addr("0.0.0.0");
	addr.sin_port         =  htons(SERV_PORT);

	//---- bind
	if (-1 == bind(listen_fd, (struct sockaddr *)&addr, addr_len)) {
		fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
		perror(" bind");
		exit(EXIT_FAILURE);
	}

	//---- listen
	if (-1 == listen(listen_fd, LISTEN_Q)) {
		fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
		perror(" listen");
		exit(EXIT_FAILURE);
	}

	//---- epoll_ctl
	ev.events  = EPOLLIN;
	ev.data.fd = listen_fd;
	if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev)) {
		fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
		perror(" epoll_ctl");
		exit(EXIT_FAILURE);
	}

	//---- main loop
	while ( SERV_RUN == serv_runing ) {
        int nfds = 0;

		printf("%s[%s Inform %s]%s", HIGH_LIGHT, F_DGREEN, COLOR_RESET, ALL_RESET);
		printf(" server will invoke epoll_wait ......\n");

        nfds = epoll_wait(epoll_fd, events, EPOLL_SIZE, -1);
		if (-1 == nfds) {
		    fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
			perror(" epoll_wait");
			continue;
		}

		printf("%s[%s Inform %s]%s", HIGH_LIGHT, F_DGREEN, COLOR_RESET, ALL_RESET);
		printf(" epoll_wait found %s%d%s events\n", F_GREEN, nfds, COLOR_RESET);

		//---- handle events
		if (nfds > 0) {
            
			int i;
			for (i = 0; i < nfds; ++i) {
                if (events[i].data.fd == listen_fd) {
					// listen event
                    tmp_fd = accept(listen_fd, (struct sockaddr*)&cli_addr, &cli_addr_len);
					if (-1 == tmp_fd) {
						// accept failed
		                fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
						perror(" accept");
		                fprintf(stderr, "%s[%s Errors %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
                        fprintf(stderr, " accept on listen_fd failed\n");
					}
					else {
						// accept successfully
                        memset(&ev, 0, sizeof(ev));

                        ev.events   =  EPOLLIN;
						ev.data.fd  =  tmp_fd;
						if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tmp_fd, &ev)) {
		                    fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
							perror(" epoll_ctl");
		                    fprintf(stderr, "%s[%s Errors %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
                            fprintf(stderr, " serve for %s%s:%d%s on fd %s%d%s failed\n", F_GREEN,  
									inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), COLOR_RESET, 
									F_GREEN, tmp_fd, COLOR_RESET);

							close(tmp_fd);
						}
						else {
                            printf("%s[%s Login  %s]%s", HIGH_LIGHT, F_YELLOW, COLOR_RESET, ALL_RESET);
							printf(" %s%s:%d%s online on fd %s%d%s\n", F_GREEN, inet_ntoa(cli_addr.sin_addr), 
									ntohs(cli_addr.sin_port), COLOR_RESET, F_GREEN, tmp_fd, COLOR_RESET);
						}
					}
				}
				else {
					// read event
                    int retval = do_echo(events[i].data.fd);
                    
                    if (-1 == retval) {
		                fprintf(stderr, "%s[%s Errors %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
                        fprintf(stderr, " read fd %s%d%s failed\n", F_GREEN, events[i].data.fd, COLOR_RESET);
					}
					
                    if (retval <= 0) {

						ev.events   =  EPOLLIN;
						ev.data.fd  =  events[i].data.fd;
						if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev.data.fd, &ev)) {
		            	    fprintf(stderr, "%s[%s SysErr %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
							perror(" epoll_ctl");
		            	    fprintf(stderr, "%s[%s Errors %s]%s", HIGH_LIGHT, F_RED, COLOR_RESET, ALL_RESET);
                    	    fprintf(stderr, " released fd %s%d%s failed\n", F_GREEN, events[i].data.fd, COLOR_RESET);
						}
						else {
		            		fprintf(stderr, "%s[%s Logout %s]%s", HIGH_LIGHT, F_YELLOW, COLOR_RESET, ALL_RESET);
                    		fprintf(stderr, " released fd %s%d%s successfully\n", F_GREEN, events[i].data.fd, COLOR_RESET);
						}
						
						close(tmp_fd);
					}
				}
			}
		}
	}

	close(epoll_fd);

	return 0;
}
