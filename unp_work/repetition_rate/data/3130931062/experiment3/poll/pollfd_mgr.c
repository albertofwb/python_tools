#include <stdio.h>
#include <poll.h>

int init_pollfd_set(struct pollfd * fds, size_t len)
{
    if ( !fds ) {
        return -1;
	}

	int i = 0;

	for (i = 0; i < len; ++i) {
        fds[i].fd = -1;
	}

	return 0;
}

int pollfd_set(struct pollfd * fds, size_t len, int fd)
{
    if ( !fds ) {
        return -1;
	}

	int i = 0;
	for (i = 0; i < len; ++i) {
    	if (-1 == fds[i].fd) {
            fds[i].fd = fd;
			return i;
		}
	}

	return -1;
}
