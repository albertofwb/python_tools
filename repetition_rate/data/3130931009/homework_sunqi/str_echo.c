#include "unp.h"
void str_echo(int sockfd){
  
 ssize_t n;
 char buf[MAXLINE];
 long num1,num2;
	
 for(;;)
 {
  if((n = Readline(sockfd,buf,MAXLINE)) == 0)
	  return;
  if((sscanf(buf,"%ld%ld",&num1,&num2))==2)
	  snprintf(buf,sizeof(buf),"%ld\n",num1+num2);
  else
	  snprintf(buf,sizeof(buf),"input error\n");
 
  n=strlen(buf);
  Writen(sockfd,buf,n);
 }


}
