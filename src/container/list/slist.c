/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/list/slist.h>

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
    if (list == NULL)
    {
        return;
    }

    while (list->front != NULL)
    {
        arc_slist_pop_front(list);
    }

    free(list);
}

/******************************************************************************/

int arc_slist_size(struct arc_slist * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size; 
}

/******************************************************************************/

int arc_slist_empty(struct arc_slist * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size == 0; 
}

/******************************************************************************/

void *arc_slist_front(struct arc_slist * list )
{
    if (list == NULL || list->front == NULL)
    {
        return NULL;
    }

    return list->front->data;
}

/******************************************************************************/

void arc_slist_pop_front(struct arc_slist * list )
{
    struct arc_slist_node *node;

    if (list == NULL || list->front == NULL)
    {
        return;
    }
    
    node = list->front;

    list->size--;
    list->front = node->next;

    free(node);
}

/******************************************************************************/

int arc_slist_push_front(struct arc_slist * list , 
                       void *data)
{
    struct arc_slist_node *node;

    if (list == NULL)
    {
        return -1;    
    }
    
    node = (struct arc_slist_node *)malloc(list->node_size);

    if (node == NULL)
    {
        return -1;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, list->data_size);

    node->next = list->front;

    list->front = node;

    list->size++;

    return 0;
}

/******************************************************************************/

void arc_slist_clear(struct arc_slist * list )
{
    if (list == NULL)
    {
        return;
    }

    while (list->front != NULL)
    {
        arc_slist_pop_front(list);
    }
}

/******************************************************************************/

struct arc_slist_node * arc_slist_begin(struct arc_slist * list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->front;
}

/******************************************************************************/

int arc_slist_insert_after(struct arc_slist * list, 
                         struct arc_slist_node * it, 
                         void * data)
{
    struct arc_slist_node * node;

    if (list == NULL || it == NULL)
    {
        return -1;
    }

    node = (struct arc_slist_node *)malloc(list->node_size);

    if (node == NULL)
    {
        return -1;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, list->data_size);

    node->next = it->next;
    it->next = node;

    list->size++;

    return 0;
}

/******************************************************************************/

int arc_slist_erase_after(struct arc_slist * list, 
                        struct arc_slist_node * it)
{
    if (list == NULL || it == NULL)
    {
        return -1;
    }

    if (it->next != NULL)
    {
        struct arc_slist_node *node = it->next;
        
        it->next = node->next;

        list->size--;

        free(node);
    }

    return 0;
}

/******************************************************************************/

void * arc_slist_iterator_data(struct arc_slist_node * it)
{
    if (it == NULL)
    {
        return NULL;
    }

    return it->data;
}

/******************************************************************************/

struct arc_slist_node * arc_slist_iterator_next(struct arc_slist_node * it)
{
    if (it == NULL)
    {
        return NULL;
    }

    return it->next;
}

/******************************************************************************/
