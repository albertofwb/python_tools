#include		"unp.h"
void
str_cli(FILE *fp, int sockfd)
{
		int			maxfdp1, stdineof;
		fd_set		rset;
		char		sendline[MAXLINE], recvline[MAXLINE];

		stdineof = 0;
		FD_ZERO(&rset);
		for ( ; ; ) 
		{
			if (stdineof == 0)
			{
				FD_SET(fileno(fp), &rset);
			}

			FD_SET(sockfd, &rset);
			maxfdp1 = max(fileno(fp), sockfd) + 1;
		    Select(maxfdp1, &rset, NULL, NULL, NULL);

			if (FD_ISSET(sockfd, &rset)) 
			{
				if (Readline(sockfd, recvline, MAXLINE) == 0) 
				{
					if (stdineof == 1)
					{
						return;
					}
					else
					{
						err_quit("str_cli: server terminated prematurely");
					}
				}
				Fputs(recvline, stdout);
			}

			if (FD_ISSET(fileno(fp), &rset)) 
			{ 
				if (Fgets(sendline, MAXLINE, fp) == NULL) 
				{
					stdineof = 1;
					Shutdown(sockfd, SHUT_WR);	
					FD_CLR(fileno(fp), &rset);
					continue;
				}
				Writen(sockfd, sendline, strlen(sendline));
			}
	}
}
