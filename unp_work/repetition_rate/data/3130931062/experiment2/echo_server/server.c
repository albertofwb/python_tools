#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>

#include <unistd.h>

#include "../../conn/conn.h"
#include "../../common_linklist/jlinklist.h"
#include "server_stat.h"

#define LISTEN_PORT  (31062)
#define LISTEN_QUEUE (24)

int  do_fork(int sockfd);
void sig_action(int sig, siginfo_t * siginfo, void * val);
void sig_action2(int sig, siginfo_t * siginfo, void * val);
void sig_action3(int sig, siginfo_t * siginfo, void * val);

Boolean func(void *data, void *attr);

listener_T   listener;

link_list_T  pros_list;

int server_runing = SERV_RUN;

int main(int argc, char * argv[])
{
    pid_t  temp_pid    = -1;
    int    temp_sockfd = -1; 

	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags     = SA_SIGINFO;
	act.sa_restorer  = NULL;
    //---- register SIGCHLD
	act.sa_sigaction = sig_action;
	if ( sigaction(SIGCHLD, &act, NULL) ) {
		goto Err0;
	}
    //---- register SIGUSR1
	act.sa_sigaction = sig_action2;
	if ( sigaction(SIGUSR1, &act, NULL) ) {
		goto Err0;
	}
    //---- initialize the listen file descriptor
	if (-1 == init_listener(&listener, "0.0.0.0", LISTEN_PORT, LISTEN_QUEUE)) {
		goto Err0;
    }
    //---- initialize the file descriptors link list
	if (-1 == init_list(&pros_list)) {
		fprintf(stderr, "[ Errors ] failed to initialize link list\n");
		destroy_listener(&listener);
		exit(EXIT_FAILURE);
	}

	printf("[  Pid   ] %d\n", getpid());

	//---- main loop
    while (server_runing == SERV_RUN) {
		
		fprintf(stdout, "[ Inform ] Listening...\n");
        
        if (-1 == (temp_sockfd = accept(listener.listen_sockfd, NULL, NULL) )) {
			if (EINTR != errno) {
				perror("[ Errors ] ");
			}
			else {
				printf("[ Inform ] EINTR occured in accept\n");
			}
            continue;
        }

        if (-1 == (temp_pid = fork())) {
            perror("[ Errors ] ");
            continue; 
        }
        else if (0 == temp_pid) {
            
			close(listener.listen_sockfd);
			
			destroy_list(&pros_list);

			// register the signal SIGUSR2
			// if received SIGUSR2, the process will exit normally
	        act.sa_sigaction = sig_action3;
	        if ( sigaction(SIGUSR2, &act, NULL) ) {
	        	perror("[ Errors ] ");
				fprintf(stderr, "[ Errors ] process exit\n");
	        	exit(EXIT_FAILURE);
	        }

			return do_fork(temp_sockfd);
        }

		close(temp_sockfd);

		if (push_back(&pros_list, &temp_pid, sizeof(pid_t))) {
            printf("[   OK   ] push process %d successfully\n", temp_pid);
			printf(">>>>>>>>>> push is %d\n", *((pid_t *)get_tail_data));
		}

        fprintf(stdout, "[ Inform ] a new client is online -> pid=[%d]\n", temp_pid);
    }

	printf("[ Inform ] server will stop\n");

	if (SERV_EXIT == server_runing) {
		// send SIGUSR2 to every child processes and wait them
		pid_t * pidptr = NULL;
        pid_t   pid    = -1;
		union sigval x;

		while ( get_list_length(&pros_list) ) {
		    pidptr = get_head_data(&pros_list);
			pid = *((pid_t *)pidptr);
			if ( pidptr ) {
				sigqueue(pid, SIGUSR2, x);
				printf("[   OK   ] send SIGUSR2 to process %d \n", pid);
				usleep(300);
			}
		}

		while ( get_list_length(&pros_list) );
	}

    destroy_listener(&listener);
	destroy_list(&pros_list);

	printf("[ Inform ] server stoped successfully\n");

    exit(EXIT_SUCCESS);

Err0:
	perror("[ Errors ] ");
	exit(EXIT_FAILURE);
}
