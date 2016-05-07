#include "unp.h"

#define WHO_AM_I   		"ALB_SAY: "
#define LISTEN_PORT 	31002
#define check_up(exp, ret)  if((exp)) {printf("error line: %d[ %s %s %s]\n", __LINE__, #exp, __func__, __FILE__); exit(ret);}

void sig_handler(int sig)
{
	int pid;
	pid = waitpid(-1, NULL, WNOHANG);
	if(0 != pid) {
		printf("recycle child [%d]\n", pid);
	}
}

int main(int argc,char **argv)
{
	int 		listenfd,connfd;
	int 		sock_opt = 1;
	pid_t		childpid;
	socklen_t 	sock_len;
	struct 		sockaddr_in cli_addr, serv_addr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	// init server set
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = 0;
	serv_addr.sin_port = htons(LISTEN_PORT);

	//set port reuseable
	check_up(-1 == setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(sock_opt)), 1);
	printf("set SO_REUSEADDR OK\n");

	Bind(listenfd, (SA *)&serv_addr, sizeof(serv_addr));
	
	Listen(listenfd,LISTENQ);
	printf("server listen on: %d\n", LISTEN_PORT);	

	check_up(SIG_ERR == signal(SIGCHLD, sig_handler), 1)
	printf("signal register OK\n");

	while(1) {
		sock_len = sizeof(cli_addr);
		connfd = Accept(listenfd, (SA *)&cli_addr, &sock_len);
		if((childpid = Fork()) == 0){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		printf("get new connection: [%s:%d]\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
		Close(connfd);
	}

}

void str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	char send_msg[MAXLINE + sizeof(WHO_AM_I)];


	while(1) {
		if((n = Readline(sockfd,line,MAXLINE)) == 0)
			return;
		strcpy(send_msg, WHO_AM_I);
		strncat(send_msg, line, n);
		n += sizeof(WHO_AM_I);
		Writen(sockfd, send_msg, n);
	}
}
