/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/list/dl_list.h>

struct dl_list_node
{
    struct dl_list_node *next;
    struct dl_list_node *previous;
    void *data;
};

struct dl_list
{
    struct dl_list_node *front;
    struct dl_list_node *back;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct dl_list * dl_list_create(size_t data_size)
{
    struct dl_list * list = (struct dl_list *)malloc(sizeof(struct dl_list));

    if (list == NULL)
    {
        return NULL;
    }

    list->front = NULL;
    list->back = NULL;
    list->size = 0;
    list->data_size = data_size;
    list->node_size = list->data_size + sizeof(struct dl_list_node);
    
    return list;
}

/******************************************************************************/

void dl_list_destroy(struct dl_list * list)
{
    if (list == NULL)
    {
        return;
    }

    // while (list->front != NULL)
    // {
    //     dl_list_pop_front(list);
    // }

    free(list);
}

/******************************************************************************/

int dl_list_size(struct dl_list * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size; 
}

/******************************************************************************/

int dl_list_empty(struct dl_list * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size == 0; 
}

/******************************************************************************/