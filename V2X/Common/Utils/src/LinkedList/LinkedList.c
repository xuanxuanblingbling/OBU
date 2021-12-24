/***********************************************************************
 * 文 件 名 称 ： LinkedList.c
 * 功 能 描 述 ： 双头链表实现
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

/*
** ===================================================================
**     Include files.
** ===================================================================
*/
#include "LinkedList.h"

#define MODULE_NAME "LINK_QUEUE"
#include "Debug.h"

/*
** ===================================================================
**     linkedlist lib.
** ===================================================================
*/
bool linkedlist_is_empty(linkedlist list)
{
    return list->head->prev == list->head->next ? true : false;
}

linkedlist linkedlist_alloc(void)
{
    MALLOC(list, linkedlist);
    if (NULL == list)
    {
        pr_err("Malloc fail!");
        return NULL;
    }
    BZERO(list, linkedlist);
    usleep(1000U);
    list->head = linkedlist_node_alloc((DATA)0, VA_ARGS_TERMINATE);
    list->tail = linkedlist_node_alloc((DATA)0, VA_ARGS_TERMINATE);
    return list;
}

linkedlist_node linkedlist_node_alloc(DATA data, ...)
{
    MALLOC(node, linkedlist_node);
    if (NULL == node)
    {
        pr_err("Malloc fail!");
        return NULL;
    }
    BZERO(node, linkedlist_node);
    node->data = data; /* The data must be the heap addr or NULL. */
    va_list arg_ptr;
    va_start(arg_ptr, data);
    int nArgValue = va_arg(arg_ptr, int); /* Get the first arg to check invlid or not. */
    va_end(arg_ptr);
    if (nArgValue != VA_ARGS_TERMINATE)
    {
        linkedlist_vargs(data, node, int);
    }
    usleep(1000U);
    return node;
}

int linkedlist_init(linkedlist list)
{
    if (!list)
    {
        list = linkedlist_alloc();
        if (!list)
        {
            pr_err("Head alloc fail!");
            return E_EXIT_ENOMEM;
        }
    }
    list->head->next = list->tail->next = NULL;
    list->head->prev = list->tail->prev = NULL;
    list->head->data = list->tail->data = (DATA)0;
    list->head->index = list->tail->index = 0;
    list->length = 0;
    return E_EXIT_OK;
}

linkedlist_node linkedlist_append(linkedlist list, DATA data)
{
    linkedlist_node node = linkedlist_node_alloc(data, VA_ARGS_TERMINATE);
    if (!node)
    {
        pr_err("Failed to alloc node!");
        return NULL;
    }
    linkedlist_append_node(list, node);
    return node;
}

linkedlist_node linkedlist_insert(linkedlist list, size_t pos, DATA data)
{
    if (!data)
    {
        pr_err("Data is nullptr!");
        return NULL;
    }

    linkedlist_node node = linkedlist_node_alloc(data, VA_ARGS_TERMINATE);
    if (!node)
    {
        pr_err("Failed to alloc node!");
        return NULL;
    }
    if (linkedlist_insert_node(list, pos, node) < 0)
    {
        pr_err("Failed to insert data!");
        return NULL;
    }
    return node;
}

linkedlist_node linkedlist_index_insert(linkedlist list, size_t pos, int *index)
{
    if (!index)
    {
        pr_err("Index is nullptr!");
        return NULL;
    }

    linkedlist_node node = linkedlist_node_alloc((DATA)NULL, index);
    if (!node)
    {
        pr_err("Failed to alloc node!");
        return NULL;
    }
    if (linkedlist_insert_node(list, pos, node) < 0)
    {
        pr_err("Failed to insert data!");
        return NULL;
    }
    return node;
}

linkedlist_node linkedlist_get_node(linkedlist list, size_t pos)
{
    linkedlist_node node = NULL;
    if (0 == pos)
    {
        pr_err("Be careful to insert data in the head.");
    }

    if (pos >= list->length)
    {
        return NULL;
    }

    if (pos > list->length / 2)
    {
        /* Here the real valid interval from tail to current.*/
        pos = list->length - pos;
        node = list->tail->prev;
        while (--pos >= 1 && node)
        {
            node = node->prev;
        }
    }
    else
    {
        pos += 1; /* Here for the first node, pos = 0, --0 is unpredictable. */
        node = list->head->next;
        while (--pos >= 1 && node)
        {
            node = node->next;
        }
    }
    return node;
}

linkedlist_node linkedlist_get_node_at_tail(linkedlist list, size_t pos)
{
    linkedlist_node node = NULL;
    if (pos >= list->length)
    {
        pr_err("Invalid param!");
        return NULL;
    }

    pos += 1;
    node = list->tail->prev;
    while (--pos >= 1 && node)
    {
        node = node->prev;
    }

    return node;
}

DATA linkedlist_get_node_data(linkedlist list, size_t pos)
{
    linkedlist_node node = linkedlist_get_node(list, pos);
    if (!node)
    {
        pr_err("Failed to get node!");
        return (DATA)0;
    }
    return node->data;
}

void linkedlist_unlink(linkedlist list, linkedlist_node node)
{
    if (list->length > 0)
    {
        list->length -= 1;
    }
    do
    {
        if (node == list->tail)
        {
            list->tail->prev->next = NULL;
            node = list->tail;
            node->prev = node->next = NULL;
            break;
        }
        if (node == list->tail->prev)
        {
            list->tail->prev = node->prev;
            node->prev->next = list->tail;
        }
        else
        {
            node->next->prev = node->prev;
            if (node->prev)
            {
                node->prev->next = node->next;
            }
        }
        node->prev = node->next = NULL;
    } while (0);
}

void linkedlist_link(linkedlist list, linkedlist_node cur, linkedlist_node node)
{
    if (cur->next)
    {
        node->next = cur->next;
        cur->next->prev = node;
        node->prev = cur;
        cur->next = node;
    }
    else
    {
        cur->next = node;
        node->prev = cur;
    }
    list->length += 1;
}

linkedlist_node linkedlist_get_node_by_data(linkedlist list, DATA data, size_t size)
{
    if (!data)
    {
        pr_err("Data is nullptr!");
        return NULL;
    }

    if (linkedlist_is_empty(list))
    {
        pr_err("linkedlist is empty.");
        return NULL;
    }

    linkedlist_node node = NULL;
    linkedlist_for_each(node, list)
    {
        if (!memcmp(node->data, data, size))
        {
            return node;
        }
    }
    return NULL;
}

linkedlist_node linkedlist_get_node_by_index(linkedlist list, int index)
{
    if (linkedlist_is_empty(list))
    {
        pr_err("linkedlist is empty.");
        return NULL;
    }

    linkedlist_node node = NULL;
    linkedlist_for_each(node, list)
    {
        if (node->index == index)
        {
            return node;
        }
    }
    return NULL;
}

void linkedlist_delete(linkedlist list, size_t pos)
{
    linkedlist_node node = linkedlist_get_node(list, pos);
    linkedlist_delete_node(list, node);
}

void linkedlist_delete_node(linkedlist list, linkedlist_node node)
{
    linkedlist_unlink(list, node);
    linkedlist_node_free(node);
}

void linkedlist_append_node(linkedlist list, linkedlist_node node)
{
    if (list->head->next)
    {
        node->prev = list->tail->prev;
        list->tail->prev->next = node;
        node->next = list->tail;
        list->tail->prev = node;
    }
    else
    {
        list->head->next = node;
        node->prev = list->head;
        node->next = list->tail;
        list->tail->prev = node;
    }
    list->length += 1;
}

int linkedlist_insert_node(linkedlist list, size_t pos, linkedlist_node node)
{
    if (!list || !node)
    {
        pr_err("Invalid param!");
        return E_EXIT_EINVAL;
    }
    linkedlist_node cur = linkedlist_get_node(list, pos);
    if (cur)
    {
        linkedlist_link(list, cur, node);
    }
    else
    {
        linkedlist_append_node(list, node);
    }
    return E_EXIT_OK;
}

void linkedlist_data_destroy(DATA data)
{
    linkedlist_node_data_free(data);
}

void linkedlist_clear_exit(linkedlist list, void (*on_destroy)(DATA))
{
    linkedlist_node node = list->head->next;
    linkedlist_node del = NULL;
    list->length = 0;
    while (node && node != list->tail)
    {
        if (node->next == list->tail)
        {
            if (node->data && on_destroy)
            {
                on_destroy(node->data);
            }
            linkedlist_node_free(node);
            break;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            del = node;
        }
        if (node->data && on_destroy)
        {
            on_destroy(node->data);
        }
        linkedlist_node_free(del);
        node = node->next;
    }
    linkedlist_node_free(list);
}

/* Keep list2 connect list1, ensure the list2 is not empty. */
void linkedlist_connect(linkedlist list1, linkedlist list2)
{
    do
    {
        if (!list2->head->next)
        {
            pr_err("List2 is empty!");
            break;
        }
        if (list1->head->next)
        {
            list2->tail->prev->next = list1->tail;
            list1->tail->prev->next = list2->head->next;
            list2->head->next->prev = list1->tail->prev;
            list1->tail->prev = list2->tail->prev;
        }
        else
        {
            list2->tail->prev->next = list1->tail;
            list1->head->next = list2->head->next;
            list1->tail->prev = list2->tail->prev;
            list2->head->next->prev = list1->head;
        }
        list1->length += list2->length;
        list2->length = 0;
        linkedlist_node_free(list2);
    } while (0);
}

void linkedlist_node_free(void *node)
{
    if (node)
    {
        free(node);
        node = NULL;
    }
}
