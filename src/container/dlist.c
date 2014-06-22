/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/dlist.h>
#include <arc/common/defines.h>

#include "iterator.h"

struct arc_dlist_node
{
    struct arc_dlist_node * next;
    struct arc_dlist_node * prev;
    char data[1];
};

struct arc_dlist
{
    struct arc_dlist_node front;
    struct arc_dlist_node back;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_dlist * arc_dlist_create(size_t data_size)
{
    size_t aligned_size;
    struct arc_dlist * list = malloc(sizeof(struct arc_dlist));

    if (list == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the 
       space occupied by the alignment */
    aligned_size = ((char *)&list->front) + 
                     sizeof(struct arc_dlist_node) - 
                     ((char *)&list->front.data);

    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    /* Initialise the list */
    list->size = 0;
    list->data_size = data_size;
    list->node_size = aligned_size + sizeof(struct arc_dlist_node);
    
    /* Initialise the first "NULL" node : it doesn't hold memory for data
       this node is refered to as the "before_begin" node */
    list->front.next = &(list->back);
    list->front.prev = NULL;

    /* Initialise the last "NULL" node : it doesn't hold memory for data
       this node is refered to as the "after_end" node, only kept for 
       comparison purposes */
    list->back.next = NULL;
    list->back.prev = &(list->front);

    return list;
}

/******************************************************************************/

void arc_dlist_destroy(struct arc_dlist * list)
{
    arc_dlist_clear(list);

    free(list);
}

/******************************************************************************/

int arc_dlist_size(struct arc_dlist * list)
{
    return list->size; 
}

/******************************************************************************/

int arc_dlist_empty(struct arc_dlist * list)
{
    return list->front.next == &(list->back); 
}

/******************************************************************************/

void arc_dlist_clear(struct arc_dlist * list)
{
    while (list->front.next != &list->back)
    {
        arc_dlist_pop_front(list);
    }
}

/******************************************************************************/

void * arc_dlist_front(struct arc_dlist * list)
{
    return &(list->front.next->data);
}

/******************************************************************************/

void arc_dlist_pop_front(struct arc_dlist * list)
{
    struct arc_iterator it;
    it.container = list;
    it.node = list->front.next;

    arc_dlist_erase(&it);
}

/******************************************************************************/

int arc_dlist_push_front(struct arc_dlist * list, void *data)
{
    struct arc_iterator it;
    it.container = list;
    it.node = &list->front;

    return arc_dlist_insert_after(&it, data);
}

/******************************************************************************/

void * arc_dlist_back(arc_dlist_t list)
{
    return &(list->back.prev->data);
}

/******************************************************************************/

void arc_dlist_pop_back(arc_dlist_t list)
{
    struct arc_iterator it;
    it.container = list;
    it.node = list->back.prev;

    arc_dlist_erase(&it);
}

/******************************************************************************/

int arc_dlist_push_back(arc_dlist_t list, void * data)
{
    struct arc_iterator it;
    it.container = list;
    it.node = &list->back;

    return arc_dlist_insert_before(&it, data);
}

/******************************************************************************/

void arc_dlist_before_begin(struct arc_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node = &(list->front);
}

/******************************************************************************/

void arc_dlist_begin(struct arc_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node = list->front.next;
}

/******************************************************************************/

void arc_dlist_end(struct arc_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node = list->back.prev;
}

/******************************************************************************/

void arc_dlist_after_end(struct arc_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node = &(list->back);
}

/******************************************************************************/

int arc_dlist_insert_before(struct arc_iterator * it, void * data)
{
    struct arc_dlist_node * current = it->node;
    struct arc_dlist * list = it->container;
    struct arc_dlist_node * node;
    struct arc_dlist_node * prev_node = current->prev;

    if (prev_node == NULL)
    {
        return ARC_ERROR;
    }

    node = malloc(list->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    /* node->data = (void *)(((char *)&node->data) + sizeof(void*)); */
    memcpy(node->data, data, list->data_size);

    node->next = current;
    node->prev = prev_node;

    prev_node->next = node;
    current->prev = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_dlist_insert_after(struct arc_iterator * it, void * data)
{
    struct arc_dlist_node * current = it->node;
    struct arc_dlist * list = it->container;
    struct arc_dlist_node * node;
    struct arc_dlist_node * next_node = current->next;

    if (next_node == NULL)
    {
        return ARC_ERROR;
    }

    node = malloc(list->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    /* node->data = (void *)(((char *)&node->data) + sizeof(void*)); */
    memcpy(node->data, data, list->data_size);

    node->next = next_node;
    node->prev = current;

    next_node->prev = node;
    current->next = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_dlist_erase(struct arc_iterator * it)
{
    struct arc_dlist_node * current = it->node;
    struct arc_dlist * list = it->container;
    struct arc_dlist_node * prev_node = current->prev;
    struct arc_dlist_node * next_node = current->next;

    if (prev_node != NULL && next_node != NULL)
    {
        prev_node->next = next_node;
        next_node->prev = prev_node;

        list->size--;

        free(current);
    }
}

/******************************************************************************/

void * arc_dlist_node_data(struct arc_iterator * it)
{
    struct arc_dlist_node * current = it->node;

    return &(current->data);
}

/******************************************************************************/

int arc_dlist_node_next(struct arc_iterator * it)
{
    struct arc_dlist_node * current = it->node;
    struct arc_dlist * list = it->container;

    if (current == &list->back)
    {
        return 0;
    }

    it->node = current->next;

    return (it->node == &list->back);
}

/******************************************************************************/

int arc_dlist_node_previous(struct arc_iterator * it)
{
    struct arc_dlist_node * current = it->node;
    struct arc_dlist * list = it->container;

    if (current == &list->front)
    {
        return 0;
    }

    it->node = current->prev;

    return (it->node == &list->front);
}

/******************************************************************************/