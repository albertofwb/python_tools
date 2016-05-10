#ifndef _CONN_H_
#define _CONN_H_

#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <stdio.h>

typedef struct {
    struct sockaddr_in addr;
    socklen_t          addr_len;
}addr_info_T;

typedef struct {
    // 本地监听的 socket
    int                listen_sockfd;
    // 本地监听信息：
    //     <1> 允许何种IP连接
    //     <2> 
    addr_info_T        addr_msg;
}listener_T;

typedef struct {
    int                sockfd;
    addr_info_T        addr_msg;
}connection_T;

/* 初始化 listener_T 类型结构体 */
int  init_listener(listener_T *plistener, char *acceptIP, int listenPort, int listenQ);

int  init_udp(listener_T *plistener, char *acceptIP, int listenPort);

/* 初始化 connetion_T 类型结构体 */
int  init_connection(connection_T *pconn, char *serverIP, int serverPort);

void destroy_listener(listener_T * plistener);

int  destroy_connection(connection_T * conn);

#endif
