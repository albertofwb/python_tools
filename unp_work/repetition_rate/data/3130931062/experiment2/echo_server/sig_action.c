#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>

#include "../../common_linklist/jlinklist.h"

extern link_list_T pros_list;

Boolean func(void * data, void * attr)
{
	if (*((pid_t *)data) == *((pid_t*)attr)) {
		return TRUE;
	}

	return FALSE;
}

void sig_action(int sig, siginfo_t * siginfo, void * val)
{
	printf("[ Inform ] child process[%d] exited with %d\n", siginfo->si_pid, siginfo->si_status);
	if (siginfo->si_pid == waitpid(siginfo->si_pid, NULL, WNOHANG)) {
		printf("[ Inform ] wait child process[%d] successfully\n", siginfo->si_pid);
	}

	if (TRUE == pop_node(&pros_list, NULL, func, &(siginfo->si_pid))) {
		printf("[   OK   ] pop process[%d] successfully\n", siginfo->si_pid);
	}
	else {
		fprintf(stderr, "[ Errors ] pop process[%d] failed\n", siginfo->si_pid);
	}
}
