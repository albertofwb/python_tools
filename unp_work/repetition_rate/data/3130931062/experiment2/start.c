#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t start_serv(const char * path)
{
    if ( !path ) {
        return -1;
	}

    pid_t child_pid = -1;

	child_pid = fork();

	if (-1 == child_pid) {
        perror("[ Errors ] ");
		return -1;
	}
	else if (0 == child_pid) {
        if ( execl(path, NULL) ) {
            perror("[ Errors ] ");
			exit(EXIT_FAILURE);
		}
	}

	return child_pid;
}
