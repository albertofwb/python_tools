#include <signal.h>

extern int cli_runing;

void sig_action3(int sig, siginfo_t * siginfo, void * val)
{
	cli_runing = 0;
}
