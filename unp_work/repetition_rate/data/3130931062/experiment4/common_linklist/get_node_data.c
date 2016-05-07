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


void * get_node_data_by_num(link_list_ptr list, int idx)
{   
    list_node_ptr ptr = NULL;

    if (NULL == list || idx <= 0 || idx > list->count) {
        return NULL;
    }
    
	int i = 0;
    ptr = list->head;
    for (i = 1; i < idx; ++i) {	
        ptr = ptr->next;
    }

	return ptr->data;
}
