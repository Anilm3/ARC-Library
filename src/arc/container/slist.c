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
#include <arc/container/slist_def.h>
#include <arc/common/defines.h>

#include <arc/container/iterator_def.h>

/******************************************************************************/

int arc_slist_initialize(struct arc_slist *list, size_t data_size)
{
    size_t aligned_size;

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

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_slist_finalize(struct arc_slist *list)
{
    arc_slist_clear(list);
}

/******************************************************************************/

struct arc_slist * arc_slist_create(size_t data_size)
{
    struct arc_slist * list = malloc(sizeof(struct arc_slist));

    if (list == NULL)
    {
        return NULL;
    }

    arc_slist_initialize(list, data_size);

    return list;
}

/******************************************************************************/

void arc_slist_destroy(struct arc_slist * list)
{
    arc_slist_finalize(list);
    free(list);
}

/******************************************************************************/

int arc_slist_insert_node_after(struct arc_slist * list,
                                 struct arc_slist_node * current,
                                 void * data)
{
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

void arc_slist_erase_node_after(struct arc_slist * list,
                                struct arc_slist_node * current)
{
    struct arc_slist_node * node = current->next;

    if (node != (struct arc_slist_node *)&(list->back))
    {
        current->next = node->next;

        list->size--;

        free(node);
    }
}

/******************************************************************************/

size_t arc_slist_size(struct arc_slist * list)
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

    arc_slist_erase_node_after(list, (struct arc_slist_node *)&(list->front));
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
    arc_slist_erase_node_after(list, (struct arc_slist_node *)&(list->front));
}

/******************************************************************************/

int arc_slist_push_front(struct arc_slist * list, void *data)
{
    return arc_slist_insert_node_after(list, 
                                       (struct arc_slist_node *)&(list->front), 
                                       data);
}

/******************************************************************************/

void arc_slist_before_begin(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    it->node_ptr = &(list->front);
}

/******************************************************************************/

void arc_slist_begin(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    it->node_ptr = list->front.next;
}

/******************************************************************************/

void arc_slist_after_end(struct arc_iterator * it)
{
    struct arc_slist * list = it->container;
    it->node_ptr = &(list->back);
}

/******************************************************************************/

int arc_slist_insert_after(struct arc_iterator * it, void * data)
{

    return arc_slist_insert_node_after(it->container, it->node_ptr, data);
}

/******************************************************************************/

void arc_slist_erase_after(struct arc_iterator * it)
{
    arc_slist_erase_node_after(it->container, it->node_ptr);
}

/******************************************************************************/

void * arc_slist_data(struct arc_iterator * it)
{
    struct arc_slist_node * current = it->node_ptr;

    return &(current->data);
}

/******************************************************************************/

int arc_slist_next(struct arc_iterator * it)
{
    struct arc_slist_node * current = it->node_ptr;
    struct arc_slist * list = it->container;

    if (current == (struct arc_slist_node *)&list->back)
    {
        return 0;
    }

    it->node_ptr = current->next;

    return (it->node_ptr != (struct arc_slist_node *)&list->back);
}

/******************************************************************************/
