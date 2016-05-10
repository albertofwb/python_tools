#include "jlinklist.h"

void check_list(link_list_ptr list)
{
    // 该函数已测试通过

    int           count = 0;
    list_node_ptr temp  = NULL;

    if (NULL == list) {
        printf("error : the pointer of list is not existed\n");
        return ;
    }

    if (0 == list->count) {
        printf("+-----------------------------\n");
        printf("| status:\n"); 
        printf("| count=%d\n", list->count);
        if (NULL == list->head) {
            printf("| [head pointer] : right\n");
        } else {
            printf("| [head pointer] : wrong\n");
        }
        if (NULL == list->tail) {
            printf("| [tail pointer] : right\n");
        } else {
            printf("| [tail pointer] : wrong\n");
        }
        printf("+-----------------------------\n");
    } else {
        printf("+-----------------------------\n");
        printf("| status:\n"); 
        printf("| count=%d\n", list->count);
        count = 0;
        temp  = list->head;
        while ( temp ) {
            count++;
            temp = temp->next;
        }
        
        if (count == list->count) {
            printf("| [NEXT-chain] : right\n");
        } else {
            printf("| [NEXT-chain] : wrong\n");
        }

        count = 0;
        temp  = list->tail;
        while ( temp ) {
            count++;
            temp = temp->prev;
        }
        
        if (count == list->count) {
            printf("| [PREV-chain] : right\n");
        } else {
            printf("| [PREV-chain] : wrong\n");
        }
        printf("+-----------------------------\n");
    }
}
