#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

void sig_action(int sig, siginfo_t * siginfo, void * val)
{
	fprintf(stdout, "[ Inform ] child process[%d] exited with %d\n", siginfo->si_pid, siginfo->si_status);
	if (siginfo->si_pid == waitpid(siginfo->si_pid, NULL, WNOHANG)) {
		fprintf(stderr, "[ Inform ] wait child process[%d] successfully\n", siginfo->si_pid);
	}
}
