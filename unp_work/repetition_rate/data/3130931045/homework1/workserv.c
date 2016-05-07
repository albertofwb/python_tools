 #include <stdio.h>                                                                                                                                                                                                                                                                                                                                                    
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <assert.h>
 #include <unistd.h>
 #include <string.h>
 #include <strings.h>
 #define MAXLINE 1000
  
  int main()
  {
      int sockfd = socket(AF_INET, SOCK_STREAM, 0);
      assert(sockfd > 0);
  
      struct sockaddr_in caddr;
      bzero(&caddr, sizeof(caddr));
      caddr.sin_family     = AF_INET;
      caddr.sin_port       = htons(31045);
      caddr.sin_addr.s_addr = inet_addr("101.200.160.104");
  
      if(0 > connect(sockfd, (struct sockaddr *)&caddr, sizeof(caddr)))
          perror("connect error");
  
      char len[MAXLINE];
     while(1)
      {
          bzero(len, MAXLINE);
          int a;
          int b;
         scanf("%d", &a);
          scanf("%d", &b);
         sprintf(len, "%d %d", a, b);
          
          write(sockfd, len, strlen(len));
          bzero(len, MAXLINE);
          read(sockfd, len, sizeof(len));
          
          printf("%s\n", len);
      }
      close(sockfd);
      return 0;
 }
