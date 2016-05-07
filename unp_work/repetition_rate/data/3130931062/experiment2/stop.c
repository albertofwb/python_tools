#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int stop_serv(pid_t serv_pid)
{
    if (0 == kill(serv_pid, SIGUSR1)) {
        return 0;
	}

	return -1;
}
