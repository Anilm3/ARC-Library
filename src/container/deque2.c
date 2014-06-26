/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/deque2.h>
#include <arc/common/defines.h>

#define INITIAL_DEQUE2_SIZE 32

struct arc_deque2
{
    unsigned size;
    unsigned allocated_size;
    unsigned start_idx;
    unsigned end_idx;
    size_t data_size;
    void * data;
    void ** data;
};

/******************************************************************************/

struct arc_deque2 * arc_deque2_create(size_t data_size)
{
    struct arc_deque2 * deque2 = malloc(sizeof(struct arc_deque2));

    if (deque2 == NULL)
    {
        return NULL;
    }

    deque2->data = malloc(INITIAL_DEQUE2_SIZE*data_size);

    if (deque2->data == NULL)
    {
        free(deque2);
        return NULL;
    }

    /* Initialise the deque2 */
    deque2->size = 0;
    deque2->allocated_size = INITIAL_DEQUE2_SIZE;
    deque2->data_size = data_size;
    deque2->start_idx = 0;
    deque2->end_idx = 0;

    return deque2;
}

/******************************************************************************/

void arc_deque2_destroy(struct arc_deque2 * deque2)
{
    free(deque2->data);
    free(deque2);
}

/******************************************************************************/

int arc_deque2_realloc(struct arc_deque2 * deque2)
{
    if (deque2->size == deque2->allocated_size)
    {
        unsigned new_size = (deque2->allocated_size*3)/2;

        void * new_data = realloc(deque2->data, deque2->data_size*new_size);

        if (new_data == NULL)
        {
            return ARC_ERROR;
        }

        deque2->data = new_data;

        if (deque2->start_idx + deque2->size > deque2->allocated_size)
        {
            /* TODO : Perform this operation as n memcpy's of non overlapping
                      blocks, it will require less copies */
            unsigned i = deque2->allocated_size - 1;
            unsigned j = new_size - 1;

            for (; i >= deque2->start_idx; i--, j--)
            {
                memcpy((char *)deque2->data + j*deque2->data_size,
                       (char *)deque2->data + i*deque2->data_size, 
                       deque2->data_size);
            }

            deque2->start_idx = j + 1;
        }

        deque2->allocated_size = new_size;
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void * arc_deque2_at(struct arc_deque2 * deque2, unsigned index)
{
    if (index < deque2->size)
    {
        index += deque2->start_idx;
        index = index % deque2->allocated_size;

        return ((char *)deque2->data) + index*deque2->data_size;
    }

    return NULL;
}

/******************************************************************************/

int arc_deque2_push_front(struct arc_deque2 * deque2, void * data)
{
    void * data_pos;

    if (arc_deque2_realloc(deque2) == ARC_ERROR)
    {
        return ARC_ERROR;
    }

    if (deque2->size > 0)
    {
        if(deque2->start_idx == 0)
        {
            deque2->start_idx = deque2->allocated_size ;
        }

        deque2->start_idx--;
    }

    data_pos = ((char *)deque2->data + deque2->start_idx*deque2->data_size);

    memcpy(data_pos, data, deque2->data_size);

    deque2->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_pop_front(struct arc_deque2 * deque2)
{
    if (deque2->size > 0)
    {
        if(++deque2->start_idx == deque2->allocated_size)
        {
            deque2->start_idx = 0;
        }

        deque2->size--;
    }
}

/******************************************************************************/

int arc_deque2_push_back(struct arc_deque2 * deque2, void * data)
{
    void * data_pos;

    if (arc_deque2_realloc(deque2) == ARC_ERROR)
    {
        return ARC_ERROR;
    }

    if (deque2->size > 0)
    {
        if(++deque2->end_idx == deque2->allocated_size)
        {
            deque2->end_idx = 0;
        }
    }

    data_pos = ((char *)deque2->data + ((size_t)deque2->end_idx)*deque2->data_size);

    memcpy(data_pos, data, deque2->data_size);

    deque2->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_pop_back(struct arc_deque2 * deque2)
{
    if (deque2->size > 0)
    {
        if(deque2->end_idx == 0)
        {
            deque2->end_idx = deque2->allocated_size;
        }

        deque2->end_idx--;
        deque2->size--;
    }
}

/******************************************************************************/

void * arc_deque2_front(struct arc_deque2 * deque2)
{
    if (deque2->size == 0)
    {
        return NULL;
    }

    return ((char *)deque2->data + ((size_t)deque2->start_idx)*deque2->data_size);
}

/******************************************************************************/

void * arc_deque2_back(struct arc_deque2 * deque2)
{
    if (deque2->size == 0)
    {
        return NULL;
    }

    return ((char *)deque2->data + ((size_t)deque2->end_idx)*deque2->data_size);
}


/******************************************************************************/

int arc_deque2_empty(struct arc_deque2 * deque2)
{
    return (deque2->size == 0);
}

/******************************************************************************/

unsigned arc_deque2_size(struct arc_deque2 * deque2)
{
    return deque2->size;
}

/******************************************************************************/

void arc_deque2_clear(struct arc_deque2 * deque2)
{
    deque2->start_idx = 0;
    deque2->end_idx = 0;
    deque2->size = 0;
}

/******************************************************************************/
