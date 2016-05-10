#include "jlinklist.h"

// ============ function definations ============

/* 通用交换函数
 *
 */
Boolean _swap(void *ptr1, void *ptr2, size_t size)
{
    void *temp = malloc(size);

    if ( !temp ) {
        return FALSE;
    }

    memcpy(temp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, temp, size);

    return TRUE;
}

/* 该函数用来申请新节点
 *
 * 参数  ：无
 * 返回值：指向节点的指针
 *
 */
list_node_ptr buy_node(size_t data_size)
{
    list_node_ptr result = NULL;

    if (NULL == (result = (list_node_ptr)malloc(sizeof(list_node_T)))) {
        return result;
    }

    if (NULL == (result->data = malloc(data_size))) {
        free(result);
        result = NULL;
        return result;
    }

    // 内存申请成功返回地址，失败返回NULL
    return result;
}

Boolean free_node(list_node_ptr * node)
{
    if (NULL == node || NULL == *node) {
        return FALSE;
    }

    free((*node)->data);
    free(*node);

    *node = NULL;

    return TRUE;
}

int get_list_length(link_list_ptr list)
{
    if (list) {
        return list->count;
    }

    return -1; 
}
