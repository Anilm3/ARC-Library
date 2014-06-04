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
    struct arc_slist * list;
    struct arc_slist_node *next;
    void *data;
};

struct arc_slist
{
    struct arc_slist_node front;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_slist * arc_slist_create(size_t data_size)
{
    struct arc_slist * list = (struct arc_slist *)malloc(sizeof(struct arc_slist));

    if (list == NULL)
    {
        return NULL;
    }

    // Initialise the list
    list->size = 0;
    list->data_size = data_size;
    list->node_size = list->data_size + sizeof(struct arc_slist_node);
    
    // Initialise the first "NULL" node : it doesn't hold memory for data
    // this node is refered to as the "before_begin" node
    list->front.list = list;
    list->front.next = NULL;
    list->front.data = NULL;

    return list;
}

/******************************************************************************/

void arc_slist_destroy(struct arc_slist * list)
{
    while (list->front.next != NULL)
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
    while (list->front.next != NULL)
    {
        arc_slist_pop_front(list);
    }
}

/******************************************************************************/

void * arc_slist_front(struct arc_slist * list)
{
    if (list->front.next == NULL)
    {
        return NULL;
    }

    return list->front.next->data;
}

/******************************************************************************/

void arc_slist_pop_front(struct arc_slist * list)
{
    struct arc_slist_node *node;

    if (list->front.next == NULL)
    {
        return;
    }
    
    node = list->front.next;

    list->size--;
    list->front.next = node->next;

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

    node->next = list->front.next;

    list->front.next = node;

    list->size++;

    return ARC_SUCCESS;
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
    return NULL;
}

/******************************************************************************/

int arc_slist_insert_after(struct arc_slist_node * current, void * data)
{
    struct arc_slist * list = current->list;
    struct arc_slist_node * node;

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

// /******************************************************************************/

int arc_slist_erase_after(struct arc_slist_node * current)
{
    struct arc_slist * list = current->list;

    if (current->next != NULL)
    {
        struct arc_slist_node * node = current->next;
        
        current->next = node->next;

        list->size--;

        free(node);
    }

    return ARC_SUCCESS;
}

// /******************************************************************************/

// int arc_slist_iterator_valid(struct arc_slist_iterator * it)
// {
//     return (it->node != NULL);
// }

// /******************************************************************************/

void * arc_slist_iterator_data(struct arc_slist_node * node)
{
    return node->data;
}

// /******************************************************************************/

struct arc_slist_node * arc_slist_iterator_next(struct arc_slist_node * node)
{
    return node->next;
}

// /******************************************************************************/

// void arc_slist_iterator_destroy(struct arc_slist_iterator * it)
// {
//     free(it);
// }

// /******************************************************************************/
