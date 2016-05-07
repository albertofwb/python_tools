#include "jlinklist.h"

Boolean pop_node(link_list_ptr list, void *data, cmp_func cmp, void *attribute)
{
    list_node_ptr ptr = NULL;

    if (NULL == list || list->count <= 0 || NULL == cmp || NULL == attribute) {
        return FALSE;
    }

    // 能执行的到这里，说明节点数大于0

    ptr = list->head;
    while ( ptr ) {
        if ( cmp(ptr->data, attribute) ) {
        // 若当前节点符合指定的属性要求
            
			// 将数据复制一份凡在用户指定的空间中
			if ( data ) {
                //memcpy(data, ptr->data, sizeof(*(ptr->data)));
            }

            if (ptr == list->head) {
            // 若找到的节点是头结点
                list->head = ptr->next; 
                if (1 != list->count) {       
                    list->head->prev = NULL;
                }
            } else if (ptr == list->tail) {
            // 若找到的节点是尾节点
                list->tail = ptr->prev;
                if (1 != list->count) {
                    list->tail->next = NULL;
                } 
            } else {
            // 若找到的节点不是头结点，也不是尾节点，
            // 即 list->count >= 3
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
            }

            free_node(&ptr);
            --(list->count);

            return TRUE;
        }

        ptr = ptr->next;
    }

    return FALSE;
}
