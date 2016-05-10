/*******select.c *********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* port we're listening on */
#define PORT 		31002
#define BUF_SIZE	1024


int main (int argc, char *argv[])
{
    fd_set master;
    /* temp file descriptor list for select() */
    fd_set read_fds;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int 	fdmax;
    int 	listener;
    int 	newfd;
	int		udpfd;
    int 	nbytes;
    char 	buf[BUF_SIZE];

    /* for setsockopt() SO_REUSEADDR, below */
    int 	yes = 1;
    int 	addrlen;
    int 	i, j;


    /* clear the master and temp sets */
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    /* get the listener */
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Server-socket() TCP lol!");
        exit(1);
    }
    printf("Server-socket() TCP is OK...\n");

    /*"address already in use" error message */
    if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1) {
        perror("Server-setsockopt() error lol!");
        exit(1);
    }
    printf("Server-setsockopt() is OK...\n");

    /* bind */
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);
    memset(&(serveraddr.sin_zero), '\0', 8);

	// bind tcp
    if(bind(listener, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) {
        perror("Server-bind() UDP error!");
        exit(1);
    }
    printf("Server-bind() is OK...\n");

    /* listen */
    if(listen(listener, 10) == -1) {
        perror("Server-listen() error lol!");
        exit(1);
    }
    printf("Server-listen() is OK...\n");

    if((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Server-socket() UDP error!");
        exit(1);
    }
    printf("Server-socket() UDP is OK...\n");

	if(bind(udpfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) {
        perror("Server-bind() EDP error !");
        exit(1);
	}

    /* add the listener to the master set */
    FD_SET(listener, &master);
	FD_SET(udpfd, &master);
    /* keep track of the biggest file descriptor */
    fdmax = udpfd;
	printf("maxfd: %d\n", fdmax);
    /* loop */
    while(1) {
        /* copy it */
        read_fds = master;
        if(select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("Server-select() error lol!");
            exit(1);
        }
        printf ("Server-select() is OK...\n");
        /*run through the existing connections looking for data to be read */
        for(i = 0; i <= fdmax; i++) {
            if(FD_ISSET(i, &read_fds)) {			/* we got one... */
                if(i == listener) {
                    /* handle new connections */
                    addrlen = sizeof(clientaddr);
                    if((newfd = accept(listener, (struct sockaddr *) &clientaddr, &addrlen)) == -1) {
                        perror("Server-accept() error lol!");
                    }else {
                        printf("Server-accept() is OK...\n");
                        FD_SET(newfd, &master);	/* add to master set */
                        if (newfd > fdmax) {	/* keep track of the maximum */
                            fdmax = newfd;
                        }
                        printf("%s: New connection from %s on socket %d\n", argv[0], inet_ntoa (clientaddr.sin_addr), newfd);
                    }
                }else if(i == udpfd) {
					memset(buf, 0, sizeof(buf));
					if((nbytes = recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr *) &clientaddr, &addrlen)) <= 0) {
						if(nbytes == 0)
							printf ("%s: socket %d hung up\n", argv[0], i);
						else
							perror ("recv() error lol!");
						close (i);
						/* remove from master set */
						FD_CLR(i, &master);
					}else{
						//buf[nbytes] = 0;
						printf("[UDP][%s:%d] %s", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);
						sendto(udpfd, buf, nbytes, 0, (struct sockaddr *) &clientaddr, addrlen);
					}
				}else {
					/* handle data from a client */
                    if((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        /* got error or connection closed by client */
                        if(nbytes == 0)
                            printf ("%s: socket %d hung up\n", argv[0], i);
                        else
                            perror ("recv() error lol!");
                        close (i);
                        /* remove from master set */
                        FD_CLR(i, &master);
                    }else {
                        write(i, buf, nbytes);
                    }
                }
            } 
        }// for (i = 0; i <= fdmax; i++)
    }// while(1) loop
    return 0;
}
