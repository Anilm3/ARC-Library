/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <string.h>
#include <arc/container/queue.h>
#include <arc/common/defines.h>

struct arc_queue_node
{
    struct arc_queue_node * next;
    void *data;
};

struct arc_queue
{
    struct arc_queue_node * front;
    struct arc_queue_node * back;
    int size;
    size_t data_size;
    size_t node_size;
};

/******************************************************************************/

struct arc_queue * arc_queue_create(size_t data_size)
{
    struct arc_queue * queue = malloc(sizeof(struct arc_queue));

    if (queue == NULL)
    {
        return NULL;
    }

    /* Initialise the list */
    queue->size = 0;
    queue->front = NULL;
    queue->back = NULL;
    queue->data_size = data_size;
    queue->node_size = data_size + sizeof(struct arc_queue_node);

    return queue;
}

/******************************************************************************/

void arc_queue_destroy(struct arc_queue * queue)
{
    arc_queue_clear(queue);
    
    free(queue);
}

/******************************************************************************/

int arc_queue_push(struct arc_queue * queue, void * data)
{
    struct arc_queue_node * node = malloc(queue->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->data = (void *)(((char *)&node->data) + sizeof(void*));
    memcpy(node->data, data, queue->data_size);

    node->next = NULL;

    if (queue->back == NULL)
    {
        queue->front = node;
    }
    else
    {
        queue->back->next = node;
    }

    queue->back = node;

    queue->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_queue_pop(struct arc_queue * queue)
{
    if (queue->front != NULL)
    {
        struct arc_queue_node * node = queue->front;
        
        if (queue->front == queue->back)
        {
            queue->front = NULL;
            queue->back = NULL;
        }
        else
        {
            queue->front = node->next;
        }
        
        queue->size--;

        free(node);
    }
}

/******************************************************************************/

void * arc_queue_front(struct arc_queue * queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }

    return queue->front->data;
}

/******************************************************************************/

void * arc_queue_back(struct arc_queue * queue)
{
    if (queue->back == NULL)
    {
        return NULL;
    }

    return queue->back->data;
}


/******************************************************************************/

int arc_queue_empty(struct arc_queue * queue)
{
    return (queue->size == 0);
}

/******************************************************************************/

int arc_queue_size(struct arc_queue * queue)
{
    return queue->size;
}

/******************************************************************************/

void arc_queue_clear(struct arc_queue * queue)
{
    while (queue->front != NULL)
    {
        arc_queue_pop(queue);
    }
}

/******************************************************************************/
