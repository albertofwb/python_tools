#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "conn/conn.h"

#define REQ 0
#define RPL 1
#define EXIT 2

typedef struct data_type {
    int32_t x;
	int32_t y;
	int32_t type;
}data_T;

int do_work(int sockfd)
{
    int runing = 1;
    data_T data;
	int32_t result;
    int  nbytes = 0;
	addr_info_T addr;

    while ( runing ) {

		printf("listening......");
        if (nbytes = recvfrom(sockfd, &data, sizeof(data_T), 0, &addr.addr, &addr.addr_len)) {
			if (-1 == nbytes) {
                return 1;
            }
            
			if (0 == nbytes) {
				return 2;
			}

			if (3 == data.type) {
				return 0;
			}

			printf("a req\n");

			result = data.x * data.y;

			sendto(sockfd, &result, sizeof(int32_t), 0, &addr.addr, addr.addr_len);
		}
    }
}
