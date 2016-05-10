
#include "conn.h"

int init_udp(listener_T *plistener, char *acceptIP, int listenPort)
{
    /* 1. 接受哪种IP的连接
     * 2. 监听端口是多少
     * 3. 等待队列长度
     */

    if (NULL == plistener || NULL == acceptIP) {
        return -1;
    }

    // 1. 创建套接字  
    if (-1 == (plistener->listen_sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
        return -1;
    }  
    
    // 2. 设置监听者的
    //    《1》通讯协议族
    //    《2》接收的连接地址
    //    《3》监听的端口  
    plistener->addr_msg.addr.sin_family      = AF_INET;          //指定网络套接字  
    plistener->addr_msg.addr.sin_addr.s_addr = htonl(INADDR_ANY);//接受所有IP地址的连接  
    plistener->addr_msg.addr.sin_port        = htons(listenPort);//绑定到端口  
    plistener->addr_msg.addr_len             = sizeof(plistener->addr_msg.addr);   
    // 3. 绑定（命名）套接字  
    if (-1 == bind(plistener->listen_sockfd,
        (struct sockaddr *)&(plistener->addr_msg.addr), 
        plistener->addr_msg.addr_len)) {
        
        return -1;
    }
    
    return 0;  
}

