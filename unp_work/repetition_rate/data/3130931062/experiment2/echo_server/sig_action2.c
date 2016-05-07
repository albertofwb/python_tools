#include <signal.h>

#include "server_stat.h"

extern int server_runing;

void sig_action2(int sig, siginfo_t * siginfo, void * val)
{
	server_runing = SERV_EXIT;
}
