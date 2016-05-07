#include "jlinklist.h"

//==== 头部插入节点
Boolean push_front(link_list_ptr list, void *data, size_t size)
{
    // 时间复杂度o(1)
    list_node_ptr node_ptr = NULL;

    if (NULL == list || NULL == data || 0 == size) {
        return FALSE;
    }

    // 若申请内存失败
    if ( !(node_ptr = buy_node(size)) ) {
        return FALSE;
    }

    memcpy(node_ptr->data, data, size);

    // 头插法每次插入节点都将成为第一个节点，
    // 所以 prev = NULL

    // 需要调整的变量：
    // <1> node_ptr 的 prev 和 next
    // <2> list_ptr 的 head
    // <3> list_ptr->head 的 prev

    // <1>
    node_ptr->prev = NULL;
    node_ptr->next = list->head;
    
    // <3>
    if ( list->head ) {
        list->head->prev = node_ptr;
    }

    // <2>
    list->head = node_ptr;

    //
    if (0 == list->count) {
        list->head = list->tail = node_ptr;   
    }

    ++(list->count);

    return TRUE;
}

//==== 尾部插入节点
Boolean push_back(link_list_ptr list, void* data, size_t size)
{
    // 时间复杂度o(1)
    
    list_node_ptr node_ptr = NULL;

    if (NULL == list || NULL == data || 0 == size) {
        return FALSE;
    }

    if ( !(node_ptr = buy_node(size)) ) {
        return FALSE;
    }
   
    memcpy(node_ptr->data, data, size);
    
    // 需要调整的变量：
    // <1> node_ptr 的 prev 和 next
    // <2> list_ptr 的 tail
    // <3> list_ptr->tail 的 next

    // <1>
    node_ptr->next = NULL;
    node_ptr->prev = list->tail;

    // <3>
    if (list->count > 0) {
        list->tail->next = node_ptr;
    } else {
        list->head = node_ptr;   
    }

    // <2>
    list->tail = node_ptr; 

    ++(list->count);
    
    return TRUE;
}
