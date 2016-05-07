#include "jlinklist.h"


/* 销毁链表
 * 
 * 参数  ：指向链表的指针
 * 返回值：无
 *
 */
void destroy_list(link_list_ptr list)
{
    // 时间复杂度o(n)，n 是链表节点数
    // 已不可再优化

    list_node_ptr temp_ptr  = NULL;
    
    if (NULL == list) {
        return ;
    }

    // the list has at least one node
    temp_ptr = list->head;
    while ( temp_ptr ) {
        list->head = temp_ptr->next;
        free(temp_ptr);
        temp_ptr = list->head;
    }

    memset(list, 0x0, sizeof(link_list_T));
}
