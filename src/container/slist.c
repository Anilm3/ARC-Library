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

struct arc_slist_node
{
    struct arc_slist_node *next;
    void *data;
};

struct arc_slist
{
    struct arc_slist_node *front;
    int size;
    size_t data_size;
    size_t node_size;
};

struct arc_slist_iterator
{
    struct arc_slist_node * node;
    struct arc_slist * list;
};

/******************************************************************************/

struct arc_slist * arc_slist_create(size_t data_size)
{
    struct arc_slist * list = (struct arc_slist *)malloc(sizeof(struct arc_slist));

    if (list == NULL)
    {
        return NULL;
    }

    list->front = NULL;
    list->size = 0;
    list->data_size = data_size;
    list->node_size = list->data_size + sizeof(struct arc_slist_node);
    
    return list;
}

/******************************************************************************/

void arc_slist_destroy(struct arc_slist * list)
{
    while (list->front != NULL)
    {
        arc_slist_pop_front(list);
    }

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
    while (list->front != NULL)
    {
        arc_slist_pop_front(list);
    }
}

/******************************************************************************/

void * arc_slist_front(struct arc_slist * list)
{
    if (list->front == NULL)
    {
        return NULL;
    }

    return list->front->data;
}

/******************************************************************************/

void arc_slist_pop_front(struct arc_slist * list)
{
    struct arc_slist_node *node;

    if (list->front == NULL)
    {
        return;
    }
    
    node = list->front;

    list->size--;
    list->front = node->next;

    free(node);
}

/******************************************************************************/

int arc_slist_push_front(struct arc_slist * list , void *data)
{
    struct arc_slist_node *node;

    node = (struct arc_slist_node *)malloc(list->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, list->data_size);

    node->next = list->front;

    list->front = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

struct arc_slist_iterator * arc_slist_begin(struct arc_slist * list)
{
    struct arc_slist_iterator * it;

    it = (struct arc_slist_iterator *)malloc(sizeof(struct arc_slist_iterator));

    if (it == NULL)
    {
        return NULL;
    }

    it->list = list;
    it->node = list->front;

    return it;
}

/******************************************************************************/

int arc_slist_insert_after(struct arc_slist_iterator * it, void * data)
{
    struct arc_slist * list = it->list;
    struct arc_slist_node * node;
    struct arc_slist_node * current = it->node;

    node = (struct arc_slist_node *)malloc(list->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, list->data_size);

    node->next = current->next;
    current->next = node;

    list->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_slist_erase_after(struct arc_slist_iterator * it)
{
    struct arc_slist * list = it->list;
    struct arc_slist_node * current = it->node;

    if (current->next != NULL)
    {
        struct arc_slist_node * node = current->next;
        
        current->next = node->next;

        list->size--;

        free(node);
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_slist_iterator_valid(struct arc_slist_iterator * it)
{
    return (it->node != NULL);
}

/******************************************************************************/

void * arc_slist_iterator_data(struct arc_slist_iterator * it)
{
    return it->node->data;
}

/******************************************************************************/

int arc_slist_iterator_next(struct arc_slist_iterator * it)
{
    if (it->node != NULL)
    {
        it->node = it->node->next;
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_slist_iterator_destroy(struct arc_slist_iterator * it)
{
    free(it);
}

/******************************************************************************/
