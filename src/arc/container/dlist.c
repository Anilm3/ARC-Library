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
#include <arc/container/dlist_def.h>
#include <arc/common/defines.h>

/******************************************************************************/

int arc_dlist_init(struct arc_dlist *list, size_t data_size)
{
    size_t aligned_size;
    /* The aligned size is the current size of the data block including the 
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_dlist_node) - 
                   ARC_OFFSETOF(struct arc_dlist_node, data);
                   /*((size_t)&(((struct arc_dlist_node *) 0)->data));*/

    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    /* Initialise the list */
    list->size = 0;
    list->data_size = data_size;
    list->node_size = aligned_size + sizeof(struct arc_dlist_node);
    
    /* Initialise the first "NULL" node : it doesn't hold memory for data
       this node is refered to as the "before_begin" node */
    list->front.next = (struct arc_dlist_node *) &(list->back);
    list->front.prev = NULL;

    /* Initialise the last "NULL" node : it doesn't hold memory for data
       this node is refered to as the "after_end" node, only kept for 
       comparison purposes */
    list->back.next = NULL;
    list->back.prev = (struct arc_dlist_node *) &(list->front);

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_dlist_fini(struct arc_dlist *list)
{
    arc_dlist_clear(list);
}

/******************************************************************************/

struct arc_dlist * arc_dlist_create(size_t data_size)
{
    struct arc_dlist * list = malloc(sizeof(struct arc_dlist));

    if (list == NULL)
    {
        return NULL;
    }

    arc_dlist_init(list, data_size);

    return list;
}

/******************************************************************************/

void arc_dlist_destroy(struct arc_dlist * list)
{
    arc_dlist_fini(list);
    free(list);
}

/******************************************************************************/

int arc_dlist_insert_node_before(struct arc_dlist * list,
                                 struct arc_dlist_node * current, 
                                 void * data)
{
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

    memcpy(node->data, data, list->data_size);

    node->next = current;
    node->prev = prev_node;

    prev_node->next = node;
    current->prev = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_dlist_insert_node_after(struct arc_dlist * list,
                                struct arc_dlist_node * current, 
                                void * data)
{
    if (current->next == NULL)
    {
        return ARC_ERROR;
    }

    return arc_dlist_insert_node_before(list, current->next, data);
}

/******************************************************************************/

void arc_dlist_erase_node(struct arc_dlist * list,
                          struct arc_dlist_node * current)
{
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

size_t arc_dlist_size(struct arc_dlist * list)
{
    return list->size;
}

/******************************************************************************/

int arc_dlist_empty(struct arc_dlist * list)
{
    return list->front.next == (struct arc_dlist_node *) &(list->back);
}

/******************************************************************************/

void arc_dlist_clear(struct arc_dlist * list)
{
    while (list->front.next != (struct arc_dlist_node *) &list->back)
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
    arc_dlist_erase_node(list, list->front.next);
}

/******************************************************************************/

int arc_dlist_push_front(struct arc_dlist * list, void *data)
{
    return arc_dlist_insert_node_after(list,
                                       (struct arc_dlist_node *)&list->front,
                                       data);
}

/******************************************************************************/

void * arc_dlist_back(arc_dlist_t list)
{
    return &(list->back.prev->data);
}

/******************************************************************************/

void arc_dlist_pop_back(arc_dlist_t list)
{
    arc_dlist_erase_node(list, list->back.prev);
}

/******************************************************************************/

int arc_dlist_push_back(arc_dlist_t list, void * data)
{
    return arc_dlist_insert_node_before(list, 
                                        (struct arc_dlist_node *)&list->back,
                                        data);
}

/******************************************************************************/

int arc_dlist_iterator_init(struct arc_dlist_iterator *it,
                            struct arc_dlist *list)
{
    it->container = list;
    it->node_ptr = NULL;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_dlist_iterator_fini(struct arc_dlist_iterator *it)
{
    it->container = NULL;
    it->node_ptr = NULL;
}

/******************************************************************************/

struct arc_dlist_iterator *arc_dlist_iterator_create(struct arc_dlist *list)
{
    struct arc_dlist_iterator *it = malloc(sizeof(struct arc_dlist_iterator));

    if (it == NULL)
    {
        return NULL;
    }

    arc_dlist_iterator_init(it, list);

    return it;
}

/******************************************************************************/

void arc_dlist_iterator_destroy(struct arc_dlist_iterator *it)
{
    arc_dlist_iterator_fini(it);
    free(it);
}

/******************************************************************************/

void arc_dlist_before_begin(struct arc_dlist_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node_ptr = &(list->front);
}

/******************************************************************************/

void arc_dlist_begin(struct arc_dlist_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node_ptr = list->front.next;
}

/******************************************************************************/

void arc_dlist_end(struct arc_dlist_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node_ptr = list->back.prev;
}

/******************************************************************************/

void arc_dlist_after_end(struct arc_dlist_iterator * it)
{
    struct arc_dlist * list = it->container;
    it->node_ptr = &(list->back);
}

/******************************************************************************/

int arc_dlist_insert_before(struct arc_dlist_iterator * it, void * data)
{
    return arc_dlist_insert_node_before(it->container, it->node_ptr, data);
}

/******************************************************************************/

int arc_dlist_insert_after(struct arc_dlist_iterator * it, void * data)
{
    return arc_dlist_insert_node_after(it->container, it->node_ptr, data);
}

/******************************************************************************/

void arc_dlist_erase(struct arc_dlist_iterator * it)
{
    arc_dlist_erase_node(it->container, it->node_ptr);
}

/******************************************************************************/

void * arc_dlist_data(struct arc_dlist_iterator * it)
{
    struct arc_dlist_node * current = it->node_ptr;

    return &(current->data);
}

/******************************************************************************/

int arc_dlist_next(struct arc_dlist_iterator * it)
{
    struct arc_dlist_node * current = it->node_ptr;
    struct arc_dlist * list = it->container;

    if (current == (struct arc_dlist_node *) &list->back)
    {
        return 0;
    }

    it->node_ptr = current->next;

    return (it->node_ptr != &list->back);
}

/******************************************************************************/

int arc_dlist_previous(struct arc_dlist_iterator * it)
{
    struct arc_dlist_node * current = it->node_ptr;
    struct arc_dlist * list = it->container;

    if (current == (struct arc_dlist_node *) &list->front)
    {
        return 0;
    }

    it->node_ptr = current->prev;

    return (it->node_ptr != &list->front);
}

/******************************************************************************/
