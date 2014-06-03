/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <pthread.h>
#include <arc/container/slist_ts.h>

struct arc_slist_ts_node
{
    struct arc_slist_ts_node *next;
    void *data;
    pthread_mutex_t *mutex;
};

struct arc_slist_ts
{
    struct arc_slist_ts_node *front;
    int size;
    size_t data_size;
    size_t node_size;
    pthread_mutex_t mutex;
};

/******************************************************************************/

struct arc_slist_ts * arc_slist_ts_create(size_t data_size)
{
    struct arc_slist_ts * list = (struct arc_slist_ts *)malloc(sizeof(struct arc_slist_ts));

    if (list == NULL)
    {
        return NULL;
    }

    list->front = NULL;
    list->size = 0;
    list->data_size = data_size;
    list->node_size = list->data_size + sizeof(struct arc_slist_ts_node);

    pthread_mutex_init(&list->mutex, NULL);

    return list;
}

/******************************************************************************/

void arc_slist_ts_destroy(struct arc_slist_ts * list)
{
    while (list->front != NULL)
    {
        arc_slist_ts_pop_front(list);
    }

    free(list);
}

/******************************************************************************/

int arc_slist_ts_size(struct arc_slist_ts * list)
{
    return list->size; 
}

/******************************************************************************/

int arc_slist_ts_empty(struct arc_slist_ts * list)
{
    return list->size == 0; 
}

/******************************************************************************/

void arc_slist_ts_clear(struct arc_slist_ts * list)
{
    while (list->front != NULL)
    {
        arc_slist_ts_pop_front(list);
    }
}

/******************************************************************************/

void * arc_slist_ts_front(struct arc_slist_ts * list)
{
    if (list->front == NULL)
    {
        return NULL;
    }

    return list->front->data;
}

/******************************************************************************/

void arc_slist_ts_pop_front(struct arc_slist_ts * list)
{
    struct arc_slist_ts_node *node;

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

int arc_slist_ts_push_front(struct arc_slist_ts * list , void *data)
{
    struct arc_slist_ts_node *node;

    node = (struct arc_slist_ts_node *)malloc(list->node_size);

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

struct arc_slist_ts_node * arc_slist_ts_begin(struct arc_slist_ts * list)
{
    return list->front;
}

/******************************************************************************/

int arc_slist_ts_insert_after(struct arc_slist_ts * list, 
                         struct arc_slist_ts_node * it, 
                         void * data)
{
    struct arc_slist_ts_node * node;

    node = (struct arc_slist_ts_node *)malloc(list->node_size);

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

int arc_slist_ts_erase_after(struct arc_slist_ts * list, struct arc_slist_ts_node * it)
{
    if (it->next != NULL)
    {
        struct arc_slist_ts_node *node = it->next;
        
        it->next = node->next;

        list->size--;

        free(node);
    }

    return 0;
}

/******************************************************************************/

void * arc_slist_ts_node_data(struct arc_slist_ts_node * it)
{
    return it->data;
}

/******************************************************************************/

struct arc_slist_ts_node * arc_slist_ts_node_next(struct arc_slist_ts_node * it)
{
    return it->next;
}

/******************************************************************************/
