/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/slist.h>
#include <arc/common/defines.h>

#include "iterator.h"

/* Sentinel node definition */
struct arc_slist_snode
{
    struct arc_slist_node * next;
};

/* Standard node definition */
struct arc_slist_node
{
    struct arc_slist_node * next;
    char data[1];
};

/* Container definition */
struct arc_slist
{
    struct arc_slist_snode front;
    struct arc_slist_snode back;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_slist * arc_slist_create(size_t data_size)
{
    size_t aligned_size;
    struct arc_slist * list = malloc(sizeof(struct arc_slist));

    if (list == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the 
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_slist_node) - 
                   ARC_OFFSETOF(struct arc_slist_node, data);
                   /* ((size_t)&(((struct arc_slist_node *) 0)->data));*/

    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    /* Initialise the list */
    list->size = 0;
    list->data_size = data_size;
    list->node_size = aligned_size + sizeof(struct arc_slist_node);
    
    /* Initialise the first "NULL" node : it doesn't hold memory for data
       this node is refered to as the "before_begin" node */
    list->front.next = (struct arc_slist_node *)&(list->back);

    /* Initialise the last "NULL" node : it doesn't hold memory for data
       this node is refered to as the "after_end" node, only kept for 
       comparison purposes */
    list->back.next = NULL;

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
    return list->front.next == (struct arc_slist_node *)&(list->back);
}

/******************************************************************************/

void arc_slist_clear(struct arc_slist * list)
{
    while (list->front.next != (struct arc_slist_node *)&(list->back))
    {
        arc_slist_pop_front(list);
    }
}

/******************************************************************************/

void * arc_slist_front(struct arc_slist * list)
{
    if (list->front.next == (struct arc_slist_node *)&(list->back))
    {
        return NULL;
    }

    return list->front.next->data;
}

/******************************************************************************/

void arc_slist_pop_front(struct arc_slist * list)
{
    struct arc_iterator it;
    it.container = list;
    it.node = &(list->front);

    arc_slist_erase_after(&it);
}

/******************************************************************************/

int arc_slist_push_front(struct arc_slist * list, void *data)
{
    struct arc_iterator it;
    it.container = list;
    it.node = &(list->front);

    return arc_slist_insert_after(&it, data);
}

/******************************************************************************/

void arc_slist_before_begin(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    it->node = &(list->front);
}

/******************************************************************************/

void arc_slist_begin(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    it->node = list->front.next;
}

/******************************************************************************/

void arc_slist_after_end(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    it->node = &(list->back);
}

/******************************************************************************/

int arc_slist_insert_after(struct arc_iterator * it, void * data)
{
    struct arc_slist * list = it->container;
    struct arc_slist_node * current = it->node;
    struct arc_slist_node * node;

    if (current == (struct arc_slist_node *)&(list->back))
    {
        return ARC_ERROR;
    }

    node = malloc(list->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    memcpy(node->data, data, list->data_size);

    node->next = current->next;
    current->next = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_slist_erase_after(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    struct arc_slist_node * current = it->node;
    struct arc_slist_node * node = current->next;

    if (node != (struct arc_slist_node *)&(list->back))
    {
        current->next = node->next;

        list->size--;

        free(node);
    }
}

/******************************************************************************/

void * arc_slist_node_data(struct arc_iterator * it)
{
    struct arc_slist_node * current = it->node;

    return &(current->data);
}

/******************************************************************************/

int arc_slist_node_next(struct arc_iterator * it)
{
    struct arc_slist_node * current = it->node;
    struct arc_slist * list = it->container;

    if (current == (struct arc_slist_node *)&list->back)
    {
        return 0;
    }

    it->node = current->next;

    return (it->node == (struct arc_slist_node *)&list->back);
}

/******************************************************************************/
