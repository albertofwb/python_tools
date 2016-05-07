#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>

int main()
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > listenfd)
	{
		perror("socket error");
	}

	struct sockaddr_in saddr;
	struct sockaddr_in caddr;

	bzero(&saddr, sizeof(struct sockaddr_in));
	bzero(&caddr, sizeof(struct sockaddr_in));

	saddr.sin_family       = AF_INET;
	saddr.sin_port         = htons(32003);
	saddr.sin_addr.s_addr  = inet_addr("101.200.160.104");

	if(-1 == bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)))
	{
		perror("bind error");
	}

	if(-1 == listen(listenfd, 5))
	{
		perror("listen error");
	}

	fd_set rfds;
	int fd[10];
	int i;
	for(i = 0; i < 10; i++)
	{
		fd[i] = -1;
	}

	fd[0] = listenfd;

	while(1)
	{
		FD_ZERO(&rfds);

		int max = -1;
		for(i = 0; i < 10; i++)
		{
			if(fd[i] != -1)
			{
				FD_SET(fd[i], &rfds);
				if(max < fd[i])
				{
					max = fd[i];
				}
			}
		}

		int n = select(max + 1, &rfds, NULL, NULL, NULL);

		if(n < 0)
		{
			perror("select error");
		}
		else if(n == 0)
		{
			printf("time out...\n");
		}
		else
		{
			for(i = 0; i < 10; i++)
			{
				if(fd[i] == -1)
				{
					continue;
				}

				if(FD_ISSET(fd[i], &rfds))
				{
					if(fd[i] == listenfd)
					{
						int len = sizeof(caddr);
						int c   = accept(listenfd, (struct sockaddr *)&caddr, &len);

						int j;
						for(j = 0; j < 10; j++)
						{
							if(fd[j] == -1)
							{
								fd[j] = c;
								break;
							}
						}
					}
					else
					{
						int x;
						char buffer[1000];
						bzero(buffer, sizeof(buffer));
						if(0 == read(fd[i], buffer, sizeof(buffer)))
						{
							close(fd[i]);
							fd[i] = -1;
							continue;
						}
						write(fd[i], buffer, strlen(buffer));
					}
				}
			}
		}
	}
	return 0;
}
