#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include <unistd.h>

#include "conn/conn.h"

#define LISTEN_PORT  (31062)
#define LISTEN_QUEUE (24)

int  do_fork(int sockfd);
void sig_action(int sig, siginfo_t * siginfo, void * val);

listener_T   listener;

int main(int argc, char * argv[])
{
    int runing = 1;

    pid_t  temp_pid    = -1;
    int    temp_sockfd = -1; 

	struct sigaction act;
	act.sa_sigaction = sig_action;
	sigemptyset(&act.sa_mask);
	act.sa_flags     = SA_SIGINFO;
	act.sa_restorer  = NULL;
	if ( sigaction(SIGCHLD, &act, NULL) ) {
		fprintf(stderr, "[ Errors ] %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (-1 == init_listener(&listener, "0.0.0.0", LISTEN_PORT, LISTEN_QUEUE)) {
        fprintf(stderr, "[ Errors ] %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    while ( runing ) {
        fprintf(stdout, "[ Inform ] Listening...\n");
         
        if (-1 == (temp_sockfd = accept(listener.listen_sockfd, NULL, NULL) )) {
            fprintf(stderr, "[ Errors ] accept error\n");
            continue;
        }

        if (-1 == (temp_pid = fork())) {
            fprintf(stderr, "[ Errors ] fork error\n");
            continue; 
        }
        else if (0 == temp_pid) {
            return do_fork(temp_sockfd);
        }

        fprintf(stdout, "[ Inform ] a new client is online -> pid=[%d]\n", temp_pid);
    }

    destroy_listener(&listener);

    exit(EXIT_SUCCESS);
}
