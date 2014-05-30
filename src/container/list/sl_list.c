/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/list/sl_list.h>

struct sl_list_node
{
    struct sl_list_node *next;
    void *data;
};

struct sl_list
{
    struct sl_list_node *front;
    int size;
    size_t data_size;
    size_t node_size;
};


/******************************************************************************/

struct sl_list * sl_list_create(size_t data_size)
{
    struct sl_list * list = (struct sl_list *)malloc(sizeof(struct sl_list));

    if (list == NULL)
    {
        return NULL;
    }

    list->front = NULL;
    list->size = 0;
    list->data_size = data_size;
    list->node_size = list->data_size + sizeof(struct sl_list_node);
    
    return list;
}

/******************************************************************************/

void sl_list_destroy(struct sl_list * list)
{
    if (list == NULL)
    {
        return;
    }

    while (list->front != NULL)
    {
        sl_list_pop_front(list);
    }

    free(list);
}

/******************************************************************************/

int sl_list_size(struct sl_list * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size; 
}

/******************************************************************************/

int sl_list_empty(struct sl_list * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size == 0; 
}

/******************************************************************************/

void *sl_list_front(struct sl_list * list )
{
    if (list == NULL || list->front == NULL)
    {
        return NULL;
    }

    return list->front->data;
}

/******************************************************************************/

void sl_list_pop_front(struct sl_list * list )
{
    struct sl_list_node *node;

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

int sl_list_push_front(struct sl_list * list , 
                       void *data)
{
    struct sl_list_node *node;

    if (list == NULL)
    {
        return -1;    
    }
    
    node = (struct sl_list_node *)malloc(list->node_size);

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

void sl_list_clear(struct sl_list * list )
{
    if (list == NULL)
    {
        return;
    }

    while (list->front != NULL)
    {
        sl_list_pop_front(list);
    }
}

/******************************************************************************/

struct sl_list_node * sl_list_begin(struct sl_list * list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->front;
}

/******************************************************************************/

int sl_list_insert_after(struct sl_list * list, 
                         struct sl_list_node * it, 
                         void * data)
{
    struct sl_list_node * node;

    if (list == NULL || it == NULL)
    {
        return -1;
    }

    node = (struct sl_list_node *)malloc(list->node_size);

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

int sl_list_erase_after(struct sl_list * list, 
                        struct sl_list_node * it)
{
    if (list == NULL || it == NULL)
    {
        return -1;
    }

    if (it->next != NULL)
    {
        struct sl_list_node *node = it->next;
        
        it->next = node->next;

        list->size--;

        free(node);
    }

    return 0;
}

/******************************************************************************/

void * sl_list_iterator_data(struct sl_list_node * it)
{
    if (it == NULL)
    {
        return NULL;
    }

    return it->data;
}

/******************************************************************************/

struct sl_list_node * sl_list_iterator_next(struct sl_list_node * it)
{
    if (it == NULL)
    {
        return NULL;
    }

    return it->next;
}

/******************************************************************************/
