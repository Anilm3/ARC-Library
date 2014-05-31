/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/list/dlist.h>

struct arc_dlist_node
{
    struct arc_dlist_node *next;
    struct arc_dlist_node *previous;
    void *data;
};

struct arc_dlist
{
    struct arc_dlist_node *front;
    struct arc_dlist_node *back;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_dlist * arc_dlist_create(size_t data_size)
{
    struct arc_dlist * list = (struct arc_dlist *)malloc(sizeof(struct arc_dlist));

    if (list == NULL)
    {
        return NULL;
    }

    list->front = NULL;
    list->back = NULL;
    list->size = 0;
    list->data_size = data_size;
    list->node_size = list->data_size + sizeof(struct arc_dlist_node);
    
    return list;
}

/******************************************************************************/

void arc_dlist_destroy(struct arc_dlist * list)
{
    if (list == NULL)
    {
        return;
    }

    // while (list->front != NULL)
    // {
    //     arc_dlist_pop_front(list);
    // }

    free(list);
}

/******************************************************************************/

int arc_dlist_size(struct arc_dlist * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size; 
}

/******************************************************************************/

int arc_dlist_empty(struct arc_dlist * list )
{
    if (list == NULL)
    {
        return -1;
    }
    
    return list->size == 0; 
}

/******************************************************************************/

struct arc_dlist_node * arc_dlist_begin(struct arc_dlist * list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->front;
}

/******************************************************************************/
