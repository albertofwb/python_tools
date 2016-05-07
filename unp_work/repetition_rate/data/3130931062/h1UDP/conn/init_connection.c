
#include "conn.h"

int init_connection(connection_T *pconn, char *serverIP, int serverPort)
{

    if (NULL == pconn || NULL == serverIP) {
        return -1;
    }
    
    // 1. 创建流套接字  
    if (-1 == (pconn->sockfd = socket(AF_INET, SOCK_STREAM, 0))) {
        return -1;
    }
    
    // 2. 初始化服务器信息
    pconn->addr_msg.addr.sin_family      = AF_INET;              //使用网络套接字  
    pconn->addr_msg.addr.sin_addr.s_addr = inet_addr(serverIP);  //服务器地址  
    pconn->addr_msg.addr.sin_port        = htons(serverPort);    //服务器所监听的端口  
    
    // 3. 连接到服务器  
    if ( connect(pconn->sockfd, (struct sockaddr *)&(pconn->addr_msg.addr), sizeof(pconn->addr_msg.addr)) )  
    {  
        return -1;
    }  

    return 0;
}

/* Name : destroy_connection - close sockfd
 * 
 * Description :
 * 
 * Parameters :
 *
 * Return Value :
 *
 */
int destroy_connection(connection_T * conn)
{
    if (NULL == conn) {
        return -1;
    }

    close(conn->sockfd);

    return 0;
}
