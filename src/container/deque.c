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
    unsigned size;
    unsigned allocated_size;
    unsigned start_idx;
    unsigned end_idx;
    size_t data_size;
    void * data;
};

/******************************************************************************/

struct arc_deque * arc_deque_create(size_t data_size)
{
    struct arc_deque * deque = malloc(sizeof(struct arc_deque));

    if (deque == NULL)
    {
        return NULL;
    }

    deque->data = malloc(INITIAL_DEQUE_SIZE*data_size);

    if (deque->data == NULL)
    {
        free(deque);
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
    free(deque->data);
    free(deque);
}

/******************************************************************************/

int arc_deque_realloc(struct arc_deque * deque)
{
    if (deque->size == deque->allocated_size)
    {
        unsigned new_size = (deque->allocated_size*3)/2;

        void * new_data = realloc(deque->data, deque->data_size*new_size);

        if (new_data == NULL)
        {
            return ARC_ERROR;
        }

        deque->data = new_data;

        if (deque->start_idx + deque->size > deque->allocated_size)
        {
            /* TODO : Perform this operation as n memcpy's of non overlapping
                      blocks, it will require less copies */
            unsigned i = deque->allocated_size - 1;
            unsigned j = new_size - 1;

            for (; i >= deque->start_idx; i--, j--)
            {
                memcpy((char *)deque->data + j*deque->data_size,
                       (char *)deque->data + i*deque->data_size, 
                       deque->data_size);
            }

            deque->start_idx = j + 1;
        }

        deque->allocated_size = new_size;
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void * arc_deque_at(struct arc_deque * deque, unsigned index)
{
    if (index < deque->size)
    {
        index += deque->start_idx;
        index = index % deque->allocated_size;

        return ((char *)deque->data) + index*deque->data_size;
    }

    return NULL;
}

/******************************************************************************/

int arc_deque_push_front(struct arc_deque * deque, void * data)
{
    void * data_pos;

    if (arc_deque_realloc(deque) == ARC_ERROR)
    {
        return ARC_ERROR;
    }

    if (deque->size > 0)
    {
        if(deque->start_idx == 0)
        {
            deque->start_idx = deque->allocated_size ;
        }

        deque->start_idx--;
    }

    data_pos = ((char *)deque->data + deque->start_idx*deque->data_size);

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

    if (arc_deque_realloc(deque) == ARC_ERROR)
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

    data_pos = ((char *)deque->data + ((size_t)deque->end_idx)*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque_pop_back(struct arc_deque * deque)
{
    if (deque->size > 0)
    {
        if(deque->end_idx == 0)
        {
            deque->end_idx = deque->allocated_size;
        }

        deque->end_idx--;
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

    return ((char *)deque->data + ((size_t)deque->start_idx)*deque->data_size);
}

/******************************************************************************/

void * arc_deque_back(struct arc_deque * deque)
{
    if (deque->size == 0)
    {
        return NULL;
    }

    return ((char *)deque->data + ((size_t)deque->end_idx)*deque->data_size);
}


/******************************************************************************/

int arc_deque_empty(struct arc_deque * deque)
{
    return (deque->size == 0);
}

/******************************************************************************/

unsigned arc_deque_size(struct arc_deque * deque)
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
