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

	if (-1 == init_udp(&listener, "0.0.0.0", LISTEN_PORT)) {
        fprintf(stderr, "[ Errors ] %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    fprintf(stdout, "[ Inform ] Listening...\n");
    do_work(listener.listen_sockfd); 

    destroy_listener(&listener);

    exit(EXIT_SUCCESS);
}
