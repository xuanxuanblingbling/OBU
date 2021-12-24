/******************************************************************************
 * 文 件 名 称 ： LinkedList.h
 * 功 能 描 述 ： 双头链表定义
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
******************************************************************************/

#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include "LinuxCommonHeader.h"
#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER

/* The linked list with head and tail, The head and tail not include any useful data.
 * the pos start from 0, and stand for the first valid node, the length is the real data length
 */
typedef struct _linkedlist_node
{
    DATA data;
    int index;
    struct _linkedlist_node *prev, *next;
} linkedlist_node_t, *linkedlist_node;

typedef struct _linkedlist
{
    size_t length;
    linkedlist_node head, tail;
} linkedlist_t, *linkedlist;

#define linkedlist_each(node, list) \
    node = (list)->head->next;      \
    node;                           \
    node = node->next

#define linkedlist_each_reverse(node, list) \
    node = (list)->tail->prev;              \
    node &&node != list->head;              \
    node = node->prev

#define linkedlist_for_each(node, list) for (linkedlist_each(node, list))
#define linkedlist_for_each_reverse(node, list) for (linkedlist_each_reverse(node, list))

#define linkedlist_node_data_alloc(data, type)                   \
    ({                                                           \
        typeof(type *) new_data = NULL;                          \
        new_data = (typeof(type *))malloc(sizeof(typeof(type))); \
        *new_data = typeof(type) data;                           \
        new_data;                                                \
    })

#define linkedlist_node_data_free(data_ptr) \
    ({                                      \
        if (data_ptr)                       \
        {                                   \
            free(data_ptr);                 \
            data_ptr = NULL;                \
        }                                   \
    })

#define linkedlist_vargs(param, node, type)                    \
    ({                                                         \
        va_list ap;                                            \
        va_start(ap, param);                                   \
        typeof(type *) index_ptr = va_arg(ap, typeof(type *)); \
        if (index_ptr)                                         \
        {                                                      \
            node->index = *index_ptr;                          \
        }                                                      \
    })

#define VA_ARGS_TERMINATE -12345

V2X_EXTERN bool linkedlist_is_empty(linkedlist list);
V2X_EXTERN linkedlist linkedlist_alloc(void);
V2X_EXTERN linkedlist_node linkedlist_node_alloc(DATA data, ...);
V2X_EXTERN linkedlist_node linkedlist_append(linkedlist list, DATA data);
V2X_EXTERN linkedlist_node linkedlist_insert(linkedlist list, size_t pos, DATA data);
V2X_EXTERN linkedlist_node linkedlist_index_insert(linkedlist list, size_t pos, int *index);
V2X_EXTERN linkedlist_node linkedlist_get_node(linkedlist list, size_t pos);
V2X_EXTERN linkedlist_node linkedlist_get_node_at_tail(linkedlist list, size_t pos);
V2X_EXTERN int linkedlist_init(linkedlist list);
V2X_EXTERN linkedlist_node linkedlist_get_node_by_data(linkedlist list, DATA data, size_t size);
V2X_EXTERN linkedlist_node linkedlist_get_node_by_index(linkedlist list, int index);
V2X_EXTERN DATA linkedlist_get_node_data(linkedlist list, size_t pos);
V2X_EXTERN void linkedlist_unlink(linkedlist list, linkedlist_node node);
V2X_EXTERN void linkedlist_link(linkedlist list, linkedlist_node cur, linkedlist_node node);
V2X_EXTERN void linkedlist_delete(linkedlist list, size_t pos);
V2X_EXTERN void linkedlist_delete_node(linkedlist list, linkedlist_node node);
V2X_EXTERN void linkedlist_append_node(linkedlist list, linkedlist_node node);
V2X_EXTERN int linkedlist_insert_node(linkedlist list, size_t pos, linkedlist_node node);
V2X_EXTERN void linkedlist_data_destroy(DATA data);
V2X_EXTERN void linkedlist_clear_exit(linkedlist list, void (*on_destroy)(DATA));
V2X_EXTERN void linkedlist_connect(linkedlist list1, linkedlist list2);
V2X_EXTERN void linkedlist_node_free(void *node);

#define LINKED_LIST_DESTROY(list, func) linkedlist_clear_exit(list, func)

V2X_END_HEADER

#endif
