#include "jlinklist.h"

void * get_head_data(link_list_ptr list)
{
    if (NULL == list) {
        return NULL;
    }

    return list->head->data;
}


void * get_tail_data(link_list_ptr list)
{
    if (NULL == list) {
        return NULL;
    }
    
    return list->tail->data;
}


void * get_node_data(link_list_ptr list, cmp_func cmp, void *attribute)
{   
    list_node_ptr ptr = NULL;

    if (NULL == list || NULL == cmp || NULL == attribute) {
        return NULL;
    }
    
    ptr = list->head;
    while ( ptr ) {
        if ( cmp(ptr->data, attribute) ) {
            return ptr->data;
        }

        ptr = ptr->next;
    }

    return NULL;
}

/*
 * Description :
 *     `idx' is the array index which is wanted to get.
 *     
 *     if `idx' is a negative value, the index of 
 *     head node is 1, the index of last node is 
 *     list.length;
 *
 *     if `idx' is a positive value, the index of 
 *     head node is list.length, the index of last node 
 *     is 1.
 */
void * get_node_data_by_index(link_list_ptr list, int idx)
{   
    list_node_ptr ptr = NULL;

    if (NULL == list || 0 == idx || abs(idx) > list->count) {
        return NULL;
    }
    
    int i    = 0;
    int loop = abs(idx);
    ptr = (idx > 0 ? list->head : list->tail);
	for (i = 1; i < loop; ++i) {	
        ptr = (idx > 0 ? ptr->next : ptr->prev);
    }

    return ptr->data;
}
