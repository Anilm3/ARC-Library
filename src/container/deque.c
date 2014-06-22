/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <string.h>
#include <arc/container/deque.h>
#include <arc/common/defines.h>

#define INITIAL_DEQUE_SIZE 32

struct arc_deque
{
    int size;
    int allocated_size;
    int start_idx;
    int end_idx;
    size_t data_size;
    char data[1];
};

/******************************************************************************/

struct arc_deque * arc_deque_create(size_t data_size)
{
    size_t aligned_size;
    size_t initial_size = INITIAL_DEQUE_SIZE*data_size;
    
    struct arc_deque * deque;

    /* The aligned size is the current size of the data block including the 
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_deque) - 
                   ARC_OFFSETOF(struct arc_deque, data);

    aligned_size = (aligned_size > initial_size ? 0 : initial_size - aligned_size);

    deque = malloc(sizeof(struct arc_deque) + aligned_size);

    if (deque == NULL)
    {
        return NULL;
    }

    /* Initialise the deque */
    deque->size = 0;
    deque->allocated_size = INITIAL_DEQUE_SIZE;
    deque->data_size = data_size;
    deque->start_idx = 0;
    deque->end_idx = 0;

    return deque;
}

/******************************************************************************/

void arc_deque_destroy(struct arc_deque * deque)
{
    arc_deque_clear(deque);
    
    free(deque);
}

/******************************************************************************/

int arc_deque_push_front(struct arc_deque * deque, void * data)
{
    void * data_pos;

    if (deque->size == deque->allocated_size)
    {
        return ARC_ERROR;
    }

    if (deque->size > 0)
    {
        if(--deque->start_idx < 0)
        {
            deque->start_idx += deque->allocated_size;
        }
    }

    data_pos = (void *)(deque->data + ((size_t)deque->start_idx)*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque_pop_front(struct arc_deque * deque)
{
    if (deque->size > 0)
    {
        if(++deque->start_idx == deque->allocated_size)
        {
            deque->start_idx = 0;
        }

        deque->size--;
    }
}

/******************************************************************************/

int arc_deque_push_back(struct arc_deque * deque, void * data)
{
    void * data_pos;

    if (deque->size == deque->allocated_size)
    {
        return ARC_ERROR;
    }

    if (deque->size > 0)
    {
        if(++deque->end_idx == deque->allocated_size)
        {
            deque->end_idx = 0;
        }
    }

    data_pos = (deque->data + ((size_t)deque->end_idx)*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque_pop_back(struct arc_deque * deque)
{
    if (deque->size > 0)
    {
        if(--deque->end_idx < 0)
        {
            deque->end_idx += deque->allocated_size;
        }

        deque->size--;
    }
}


/******************************************************************************/

void * arc_deque_front(struct arc_deque * deque)
{
    if (deque->size == 0)
    {
        return NULL;
    }

    return (deque->data + ((size_t)deque->start_idx)*deque->data_size);
}

/******************************************************************************/

void * arc_deque_back(struct arc_deque * deque)
{
    if (deque->size == 0)
    {
        return NULL;
    }

    return (deque->data + ((size_t)deque->end_idx)*deque->data_size);
}


/******************************************************************************/

int arc_deque_empty(struct arc_deque * deque)
{
    return (deque->size == 0);
}

/******************************************************************************/

int arc_deque_size(struct arc_deque * deque)
{
    return deque->size;
}

/******************************************************************************/

void arc_deque_clear(struct arc_deque * deque)
{
    deque->start_idx = 0;
    deque->end_idx = 0;
    deque->size = 0;
}

/******************************************************************************/
