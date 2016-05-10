#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
//#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT (1998)
#define LISTENQ     (5)
#define BUFFER_SIZE (1024)


int runing = 1;

int main(int argc, char * argv[])
{
	int                listen_sockfd = -1;
	int                client_sockfd = -1;
	struct sockaddr_in addr;

	time_t             ti;
	struct tm *        struct_ti;

	char               buffer[BUFFER_SIZE];

	listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listen_sockfd) {
		fprintf(stderr, "[ Failed ] failed to create a sockfd\n");
		exit(EXIT_FAILURE);
	}

	addr.sin_family       = AF_INET;
	addr.sin_addr.s_addr  = inet_addr("0.0.0.0");
	addr.sin_port         = htons(SERVER_PORT);

	if (-1 == bind(listen_sockfd, (struct sockaddr *)&addr, sizeof(addr)) ) {
		fprintf(stderr, "[ Failed ] failed to bind\n");
		close(listen_sockfd);
		exit(EXIT_FAILURE);
	}

	if (-1 == listen(listen_sockfd, LISTENQ)) {
		fprintf(stderr, "[ Failed ] failed to listen\n");
		close(listen_sockfd);
		exit(EXIT_FAILURE);
	}

	while ( runing ) {
		client_sockfd = accept(listen_sockfd, NULL, NULL);
		if (-1 == client_sockfd) {
			fprintf(stderr, "[ Failed ] failed to listen\n");
			continue;
		}
		printf("[ LOGIN ] a net client is here\n");
		ti            = time( NULL );
		struct_ti     = gmtime(&ti);
		memset(buffer, 0x0, BUFFER_SIZE);
		strftime(buffer, BUFFER_SIZE, "%Y-%m-%d-%X\n", struct_ti);
		write(client_sockfd, buffer, strlen(buffer));
		close(client_sockfd);
	} 

	close(listen_sockfd);	

	exit(EXIT_SUCCESS);
}
