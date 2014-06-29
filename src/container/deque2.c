/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <arc/container/deque2.h>
#include <arc/common/defines.h>

#define INITIAL_DEQUE2_SIZE 32
#define BLOCK_SIZE 128
#define INITIAL_NUM_BLOCKS 64

struct arc_deque2
{
    unsigned size;
    unsigned num_blocks;
    unsigned start_idx;
    unsigned end_idx;
    size_t data_size;
    void ** data;
};

/******************************************************************************/

struct arc_deque2 * arc_deque2_create(size_t data_size)
{
    struct arc_deque2 * deque = malloc(sizeof(struct arc_deque2));

    if (deque == NULL)
    {
        return NULL;
    }

    /* Initialise the deque */
    deque->size = 0;
    deque->data_size = data_size;
    deque->num_blocks = INITIAL_NUM_BLOCKS;
    deque->start_idx = BLOCK_SIZE - 1;
    deque->end_idx = BLOCK_SIZE - 1;

    deque->data = malloc(INITIAL_NUM_BLOCKS*sizeof(void *));

    if (deque->data == NULL)
    {
        free(deque);
        return NULL;
    }

    bzero(deque->data, INITIAL_NUM_BLOCKS*sizeof(void *));

    deque->data[0] = malloc(BLOCK_SIZE*data_size);

    if (deque->data == NULL)
    {
        free(deque->data);
        free(deque);
        return NULL;
    }

    return deque;
}

/******************************************************************************/

void arc_deque2_destroy(struct arc_deque2 * deque)
{
    unsigned i;

    for (i = 0; i < deque->num_blocks; i++)
    {
        free (deque->data[i]);
    }

    free(deque->data);
    free(deque);
}

/******************************************************************************/

int arc_deque2_realloc(struct arc_deque2 * deque)
{
    if (deque->size == (deque->num_blocks * BLOCK_SIZE))
    {
        unsigned new_num_blocks = (deque->num_blocks*3)/2;

        void * new_data = realloc(deque->data, new_num_blocks*sizeof(void *));

        if (new_data == NULL)
        {
            return ARC_ERROR;
        }

        deque->data = new_data;

        if (deque->start_idx + deque->size > deque->num_blocks * BLOCK_SIZE)
        {
            unsigned i, copy_size, new_start_block;
            unsigned start_block = deque->start_idx / BLOCK_SIZE;
            unsigned end_block = deque->end_idx / BLOCK_SIZE;

            if (start_block != end_block)
            {
                copy_size = deque->num_blocks - start_block;
                new_start_block = new_num_blocks - copy_size;

                memmove(&deque->data[new_start_block],
                        &deque->data[start_block],
                        copy_size*sizeof(void *));

                deque->start_idx = new_start_block * BLOCK_SIZE;
            }
            else
            {
                copy_size = deque->num_blocks - (start_block + 1);
                new_start_block = new_num_blocks - copy_size;

                memmove(&deque->data[new_start_block],
                        &deque->data[start_block + 1],
                        copy_size*sizeof(void *));

                new_start_block--;
                deque->data[new_start_block] = malloc(BLOCK_SIZE*deque->data_size);

                memcpy(deque->data[new_start_block], 
                       deque->data[start_block],
                       BLOCK_SIZE*deque->data_size);

                deque->start_idx = new_start_block * BLOCK_SIZE +
                                   deque->start_idx % BLOCK_SIZE;
            }

            for (i = end_block + 1; i < new_start_block; i++)
            {
                deque->data[i] = NULL;
            }
        }
        else
        {
            unsigned i;
            unsigned end_block = 1 + deque->end_idx / BLOCK_SIZE;

            for (i = end_block; i < new_num_blocks; i++)
            {
                deque->data[i] = NULL;
            }
        }

        deque->num_blocks = new_num_blocks;
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void * arc_deque2_at(struct arc_deque2 * deque, unsigned index)
{
    if (index < deque->size)
    {
        unsigned block_num, block_idx;

        index = (deque->start_idx + index) % (deque->num_blocks * BLOCK_SIZE);
        block_num = index / BLOCK_SIZE;
        block_idx = index % BLOCK_SIZE;

        return ((char *)deque->data[block_num] + block_idx*deque->data_size);
    }

    return NULL;
}

/******************************************************************************/

int arc_deque2_push_front(struct arc_deque2 * deque, void * data)
{
    unsigned block_num;
    unsigned block_idx;
    void * data_pos;

    if (arc_deque2_realloc(deque) == ARC_ERROR)
    {
        return ARC_ERROR;
    }

    if (deque->size > 0)
    {
        if(deque->start_idx == 0)
        {
            deque->start_idx = deque->num_blocks * BLOCK_SIZE;
        }

        deque->start_idx--;
    }

    block_num = deque->start_idx / BLOCK_SIZE;
    block_idx = deque->start_idx % BLOCK_SIZE;

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(BLOCK_SIZE*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_pop_front(struct arc_deque2 * deque)
{
    if (deque->size > 0)
    {
        if(++deque->start_idx == deque->num_blocks * BLOCK_SIZE)
        {
            deque->start_idx = 0;
        }

        deque->size--;
    }
}

/******************************************************************************/

int arc_deque2_push_back(struct arc_deque2 * deque, void * data)
{
    unsigned block_num;
    unsigned block_idx;
    void * data_pos;

    if (arc_deque2_realloc(deque) == ARC_ERROR)
    {
        return ARC_ERROR;
    }

    if (deque->size > 0)
    {
        if(++deque->end_idx == deque->num_blocks * BLOCK_SIZE)
        {
            deque->end_idx = 0;
        }
    }

    block_num = deque->end_idx / BLOCK_SIZE;
    block_idx = deque->end_idx % BLOCK_SIZE;

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(BLOCK_SIZE*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_pop_back(struct arc_deque2 * deque)
{
    if (deque->size > 0)
    {
        if(deque->end_idx == 0)
        {
            deque->end_idx = deque->num_blocks * BLOCK_SIZE;
        }

        deque->end_idx--;
        deque->size--;
    }
}

/******************************************************************************/

void * arc_deque2_front(struct arc_deque2 * deque)
{
    unsigned block_num = deque->start_idx / BLOCK_SIZE;
    unsigned block_idx = deque->start_idx % BLOCK_SIZE;

    if (deque->size == 0)
    {
        return NULL;
    }
    
    return ((char *)deque->data[block_num] + block_idx*deque->data_size);
}

/******************************************************************************/

void * arc_deque2_back(struct arc_deque2 * deque)
{
    unsigned block_num = deque->end_idx / BLOCK_SIZE;
    unsigned block_idx = deque->end_idx % BLOCK_SIZE;

    if (deque->size == 0)
    {
        return NULL;
    }
    
    return ((char *)deque->data[block_num] + block_idx*deque->data_size);
}


/******************************************************************************/

int arc_deque2_empty(struct arc_deque2 * deque)
{
    return (deque->size == 0);
}

/******************************************************************************/

unsigned arc_deque2_size(struct arc_deque2 * deque)
{
    return deque->size;
}

/******************************************************************************/

void arc_deque2_clear(struct arc_deque2 * deque)
{
    deque->start_idx = 0;
    deque->end_idx = 0;
    deque->size = 0;
}

/******************************************************************************/
