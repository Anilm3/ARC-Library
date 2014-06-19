/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

/**
 * TODO : Add slist back to first next node
 */

#include <string.h>
#include <arc/container/slist.h>
#include <arc/common/defines.h>

struct arc_slist_node
{
    struct arc_slist * list;
    struct arc_slist_node * next;
    void *data;
};

struct arc_slist
{
    struct arc_slist_node front;
    struct arc_slist_node back;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_slist * arc_slist_create(size_t data_size)
{
    struct arc_slist * list = malloc(sizeof(struct arc_slist));

    if (list == NULL)
    {
        return NULL;
    }

    /* Initialise the list */
    list->size = 0;
    list->data_size = data_size;
    list->node_size = data_size + sizeof(struct arc_slist_node);
    
    /* Initialise the first "NULL" node : it doesn't hold memory for data
       this node is refered to as the "before_begin" node */
    list->front.list = list;
    list->front.next = &(list->back);
    list->front.data = NULL;

    /* Initialise the last "NULL" node : it doesn't hold memory for data
       this node is refered to as the "after_end" node, only kept for 
       comparison purposes */
    list->back.list = list;
    list->back.next = NULL;
    list->back.data = NULL;

    return list;
}

/******************************************************************************/

void arc_slist_destroy(struct arc_slist * list)
{
    arc_slist_clear(list);

    free(list);
}

/******************************************************************************/

int arc_slist_size(struct arc_slist * list)
{
    return list->size; 
}

/******************************************************************************/

int arc_slist_empty(struct arc_slist * list)
{
    return list->size == 0; 
}

/******************************************************************************/

void arc_slist_clear(struct arc_slist * list)
{
    while (list->front.next != &(list->back))
    {
        arc_slist_pop_front(list);
    }
}

/******************************************************************************/

void * arc_slist_front(struct arc_slist * list)
{
    if (list->front.next == &(list->back))
    {
        return NULL;
    }

    return list->front.next->data;
}

/******************************************************************************/

void arc_slist_pop_front(struct arc_slist * list)
{
    arc_slist_erase_after(&list->front);
}

/******************************************************************************/

int arc_slist_push_front(struct arc_slist * list, void *data)
{
    return arc_slist_insert_after(&list->front, data);
}

/******************************************************************************/

struct arc_slist_node * arc_slist_before_begin(struct arc_slist * list)
{
    return &(list->front);
}

/******************************************************************************/

struct arc_slist_node * arc_slist_begin(struct arc_slist * list)
{
    return list->front.next;
}

/******************************************************************************/

struct arc_slist_node * arc_slist_after_end(struct arc_slist * list)
{
    return &(list->back);
}

/******************************************************************************/

int arc_slist_insert_after(struct arc_slist_node * current, void * data)
{
    struct arc_slist * list = current->list;
    struct arc_slist_node * node;

    if (current == &(list->back))
    {
        return ARC_ERROR;
    }

    node = malloc(list->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, list->data_size);

    node->list = list;
    node->next = current->next;
    current->next = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_slist_erase_after(struct arc_slist_node * current)
{
    struct arc_slist * list = current->list;

    if (current->next != &(list->back))
    {
        struct arc_slist_node * node = current->next;
        
        current->next = node->next;

        list->size--;

        free(node);
    }
}

/******************************************************************************/

void * arc_slist_node_data(struct arc_slist_node * node)
{
    return node->data;
}

/******************************************************************************/

struct arc_slist_node * arc_slist_node_next(struct arc_slist_node * node)
{
    return node->next;
}

/******************************************************************************/
