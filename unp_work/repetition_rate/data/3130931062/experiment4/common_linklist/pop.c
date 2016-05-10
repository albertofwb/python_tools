#include "jlinklist.h"

/* 弹出第一个节点
 *
 * 链表非空则弹出第一个节点，否则不操作，
 * 并不返回是否删除成功的状态
 *
 */
Boolean pop_front(link_list_ptr list, void *data)
{
    // 时间复杂度o(1)

    list_node_ptr pop_node = NULL;
    
    // 链表节点数 >= 1 时才能 pop

    // list == NULL 表示链表控制信息不存在（链表未初始化）
    // list->count == 0 表示链表为空
    if (NULL == list || list->count <= 0) {
        return FALSE;
    }

    if (1 == list->count) {
        if ( data ) {
            memcpy(data, list->head, sizeof(*(list->head)));
        }
        free_node(&(list->head));
        
        list->head = list->tail = NULL;
    } else {
        pop_node       = list->head;
        list->head = pop_node->next;
        list->head->prev = NULL;
        
        if ( data ) {
            memcpy(data, pop_node->data, sizeof(*(pop_node->data)));
        }
        free_node(&pop_node);
    }

    --(list->count);

    return TRUE;
}

/* 弹出倒数第一个节点 */
Boolean pop_back(link_list_ptr list, void *data)
{
    // 时间复杂度o(1)

    if (NULL == list || list->count <= 0 || NULL == data) {
        return FALSE;
    }

    if (1 == list->count) {
        if ( data ) {
            memcpy(data, list->tail->data, sizeof(*(list->tail->data)));
        }
        free_node(&(list->tail));

        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        
        if ( data ) {
            memcpy(data, list->tail->data, sizeof(*(list->tail->data)));
        }
        free_node(&(list->tail->next));
        
        list->tail->next = NULL;
    }

    --(list->count);

    return TRUE;
}
