#include    <arpa/inet.h>
#include    <stdlib.h>
#include    <netdb.h>
#include    <stdio.h>
#include    <string.h>

#define SIZE 8192

void err_sys(const char *p_error);

int deal_client_request(const char *domain_name, char *respond)
{
    int     i;
    int     h_err;            /* indicate error */
    char    ip[INET_ADDRSTRLEN];    /* store IP address */
    char    buf[SIZE];
    char    tmp[1024] = {0};
    struct  hostent ret, *result;
    int     tret = 0;

    if(NULL == respond || NULL == domain_name){
        return 1;
    }

    tret = gethostbyname_r(domain_name, &ret, buf, SIZE, &result, &h_err);

    if (tret != 0){
        printf("ret is %d\n", tret);
        sprintf(respond, "gethostbyname_r error: %s\n", strerror(h_err));
        return 1;
    }


    /* official hostname */
    sprintf(tmp, "official name: %s\n", result->h_name);
    strcpy(respond, tmp);
    /* output all aliases */
    for (i = 0; result->h_aliases[i] != NULL; i++) {
        sprintf(tmp, "aliases: %s\n", result->h_aliases[i]);
        strcat(respond, tmp);
    }
    /* output all IP address */
    for (i = 0; result->h_addr_list[i] != NULL; i++) {
        if (inet_ntop(AF_INET, result->h_addr_list[i], ip, sizeof(ip)) != NULL) {
            sprintf(tmp, "ip address: %s\n", ip);
            strcat(respond, tmp);
        } else{
            strcat(respond, "inet_ntop error");
        }
    }

    return 0;
}

#if 0
int main(int argc, char *argv[])
{
    char    buf[SIZE];
    //char    domain[] = "www.baidu.com";
    char    *host;
    int     ret = 0;
    int     loop = 0;

    if(argc < 2){
        exit(1);
    }

    for(loop = 1; loop < argc; loop++){
        host = argv[loop];
        ret = deal_client_request(host, buf);
        printf("ret:%d\n%s", ret, buf);
    }

    return 0;
}
#endif
