#include <stdio.h>                                                                                                       
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#define MAXLINE  1000

void sig_chld(int sig)
{
	    wait();
}

void str_echo(int c)
{
	    char line[MAXLINE] = "0";
		    while(0 < read(c, line, sizeof(line)))
				    {
						        write(c, line, strlen(line));
								        bzero(line, MAXLINE);
										    }
}

int main()
{
	    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		    assert(sockfd != -1);
			    struct sockaddr_in saddr;
				    struct sockaddr_in caddr;
					    bzero(&saddr, sizeof(saddr));
						    bzero(&caddr, sizeof(caddr));
							    saddr.sin_family       = AF_INET;
								    saddr.sin_port        = htons(31022);
									    saddr.sin_addr.s_addr = inet_addr("101.200.160.104");

										    if(0 > bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)))
												        perror("bind error");

											    if(0 > listen(sockfd, 5))
													        perror("listen error");

												    signal(SIGCHLD, sig_chld);

													    while(1)
															    {
																	        int len = sizeof(caddr);
																			        int c = accept(sockfd, (struct sockaddr *)&caddr, &len);
																					        
																					        pid_t pid = fork();
																							        if(pid == 0)
																										        {
																													            close(sockfd);
																																            
																																            str_echo(c);
																																			        
																																			            exit(0);                                                                                                     
																																						        }
																									        close(c);
																											    }

														    close(sockfd);
															    return 0;
}                               

