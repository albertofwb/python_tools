#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char serv_path[] = "./echo_server/server";

pid_t start_serv(const char * path);
int   stop_serv(pid_t serv_pid);

static void usage()
{
	printf("\n");
	printf("ctrl <start|stop>");
}

pid_t serv_pid = -1;

int main(int argc, char * argv[])
{
    if (argc != 2) {
        usage();
		exit(EXIT_FAILURE);
	}

	if ( !strcmp("start", argv[1]) ) {
        if ((serv_pid = start_serv(serv_path)) != -1) {
            printf("[   OK   ] started successfully\n");
		}
		else {
			fprintf(stderr, "[ Errors ] start failed\n");
		}
	}
	else if ( !strcmp("stop", argv[1]) ) {
        if (stop_serv(serv_pid) == 0) {
            printf("[   OK   ] stoped successfully\n");
		}
		else {
			fprintf(stderr, "[ Errors ] stop failed\n");
		}
	}
	else {
        usage();
	}

	exit(EXIT_SUCCESS);;
}
