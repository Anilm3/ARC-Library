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
#include <arc/container/queue_def.h>
#include <arc/common/defines.h>

/******************************************************************************/

struct arc_queue * arc_queue_create(size_t data_size)
{
    size_t aligned_size;

    struct arc_queue * queue = malloc(sizeof(struct arc_queue));

    if (queue == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the 
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_queue_node) - 
                   ARC_OFFSETOF(struct arc_queue_node, data);

    /* The aligment is taken into account to optimize the memory usage */
    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    /* Initialise the list */
    queue->size = 0;
    queue->front = NULL;
    queue->back = NULL;
    queue->data_size = data_size;
    queue->node_size = aligned_size + sizeof(struct arc_queue_node);

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
        
        /* The same node is the front and the back, there's only one left*/
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
    while (queue->size > 0)
    {
        arc_queue_pop(queue);
    }
}

/******************************************************************************/
