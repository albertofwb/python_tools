#include "unp.h"



//信号处理函数
void sig_chld(int signo)
{
    pid_t  pid;
    int  stat;

    while((pid=waitpid(-1,&stat,WNOHANG))>0)
        printf("child %d terminated\n",pid);
    return;
}
