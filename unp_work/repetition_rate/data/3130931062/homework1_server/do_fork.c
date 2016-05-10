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

#define BUFFER_SIZE (1024)

int do_fork(int sockfd)
{
    int runing = 1;
    data_T data;
	int32_t result;
	char buf[BUFFER_SIZE];
    int  nbytes = 0;

    while ( runing ) {
        if (nbytes = read(sockfd, &data, sizeof(data_T))) {
            if (-1 == nbytes) {
                return 1;
            }
            
			if (0 == nbytes) {
				return 2;
			}

			if (3 == data.type) {
				return 0;
			}

			result = data.x * data.y;

			write(sockfd, &result, sizeof(int32_t));
		}
    }
}
