#ifndef _JLINKLIST_H_
#define _JLINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef _JWD_BOOLEAN_T

  #define _JWD_BOOLEAN_T 1

  #define TRUE   (1)
  #define FALSE  (0)
  typedef unsigned char Boolean;

#endif


/* +-------------------------------------+
 * | 本链表库定义的数据类型              |
 * +-------------------------------------+
 * list_node_T
 * list_node_ptr
 * link_list_T
 * link_list_ptr
 *
 */


// 链表节点数据结构
typedef struct node
{
    void        *data;
    struct node *prev;
    struct node *next;
}list_node_T;

typedef list_node_T * list_node_ptr;

// 链表数据结构
typedef struct linked_list
{
    list_node_ptr head;
    list_node_ptr tail;
    int           count;
}link_list_T;

typedef link_list_T * link_list_ptr;

// 查询时需要的比较函数
typedef Boolean (*cmp_func)(void * data, void *attr);


// 链表节点数据域的大小
//#define DATA_SIZE (sizeof(list_node_T) - sizeof(list_node_ptr))

//#define swap(x, y, z) (_swap(x, y, sizeof(z)))



// ============ function declarations ============

Boolean _swap(void *ptr1, void *ptr2, size_t size);

list_node_ptr  buy_node(size_t data_size);
Boolean        free_node(list_node_ptr * node);

Boolean        init_list(link_list_ptr list);
void           destroy_list(link_list_ptr list);

int            get_list_length(link_list_ptr list);

//   +---------------+
//   | 增加/删除节点 |
//   +---------------+
Boolean        push_front(link_list_ptr list, void *data, size_t size);
Boolean        push_back(link_list_ptr list, void *data, size_t size);

Boolean        pop_front(link_list_ptr list, void *data);
Boolean        pop_back(link_list_ptr list, void *data);

Boolean        pop_node(link_list_ptr list, void *data, cmp_func cmp, void *attribute);

//   +------------------+
//   | 获取节点中的数据 |
//   +------------------+
void *         get_head_data(link_list_ptr list);
void *         get_tail_data(link_list_ptr list);

void *         get_node_data(link_list_ptr list, cmp_func cmp, void *attribute);

void *         get_node_data_by_index(link_list_ptr list, int idx);


// 克隆链表
//link_list_ptr  clone_list(link_list_ptr list_ptr);

// 反转链表
//Boolean        reverse_list(link_list_ptr list_ptr);

//Boolean        has_circle(link_list_ptr list_ptr);
//Boolean        has_circle_v2(link_list_ptr list_ptr);
//list_node_ptr  get_first_circle_node(link_list_ptr list_ptr);

void check_list(link_list_ptr list);

#endif
