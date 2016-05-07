#include "jlinklist.h"

//==== init_list 函数用来为链表控制信息申请内存
Boolean init_list(link_list_ptr list)
{
    if (NULL == list) {
        return FALSE;
    }

    memset(list, 0x0, sizeof(link_list_T));

    return TRUE;
}
