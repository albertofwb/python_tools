#ifndef _POLLFD_MGR_H_
#define _POLLFD_MGR_H_

#include <poll.h>

/* Name : init_pollfd_set - set all `fds' to -1
 *
 * Return Value: On success, 0 is returned.
 *               On failure, -1 is returned.
 */
int init_pollfd_set(struct pollfd * fds, size_t len);
/* Name : pollfd_set - add `fd' to a empty position in fds
 *
 * Return Value: On success, the index is returnd.
 *               On failure, -1 is returned.
 */
int pollfd_set(struct pollfd * fds, size_t len, int fd);

#endif
