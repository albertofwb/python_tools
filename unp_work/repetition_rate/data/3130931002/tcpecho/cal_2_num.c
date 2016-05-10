#include "unp.h"

#define LISTEN_PORT 	31002
#define EXIT_GREETINGS  "bye-bye\n"
#define check_up(exp, ret)  if((exp)) {printf("error line: %d[ %s %s %s]\n", __LINE__, #exp, __func__, __FILE__); exit(ret);}

typedef struct Calculator {
	int		num1;
	int		num2;
	char	opt;
}Calculator;

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

int cal_2_num(Calculator *input)
{
	int	rst = 0;
	if(NULL == input){
		return -1;
	}
	switch(input->opt){
		case '+':
			rst = input->num1 + input->num2;
			break;
		case '-':
			rst = input->num1 - input->num2;
			break;
		case '*':
			rst = input->num1 * input->num2;
			break;
		default:
			rst = -1;
			break;
	}
	return rst;
}

void strip(char *words, int len)
{
	int  	pos = 0;
	int		tpos = 0;
	char 	tmp[MAXLINE];

	if(NULL == words || len < 0)
		return;
	while(pos != len || 0 != words[pos]) {
		if(' ' != words[pos])
			tmp[tpos++] = words[pos];
		pos += 1;
	}
	strncpy(words, tmp, len);
}

void str_echo(int sockfd)
{
	char 		line[MAXLINE];
	char 		back_line[MAXLINE];
	int			match_items = 0;
	ssize_t 	msg_len;
	Calculator	input_exp = { 0 };


	while(1) {
		if((msg_len = Readline(sockfd, line, MAXLINE)) == 0){
			write(sockfd, EXIT_GREETINGS, sizeof EXIT_GREETINGS);
			return;
		}

		strncpy(back_line, line, msg_len);
		// delete the '\n'
		back_line[msg_len-1] = 0;

		// delete blanks in line
		strip(line, msg_len);
		match_items = sscanf(line, "%d%c%d", &input_exp.num1, &input_exp.opt, &input_exp.num2);
		if(3 != match_items){
			strcpy(line, "invalid input:\n");
			printf("match_items %d\n", match_items);
			printf("%d %c %d\n", input_exp.num1, input_exp.opt, input_exp.num2);
		}else{
			snprintf(line, MAXLINE, "%s = %d\n", back_line, cal_2_num(&input_exp));
		}
		msg_len = strnlen(line, MAXLINE);
		Writen(sockfd, line, msg_len);
	}
}
