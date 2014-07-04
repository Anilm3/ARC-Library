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

#include "iterator.h"

#define BLOCK_SIZE 32
#define INITIAL_NUM_BLOCKS 8

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
    deque->start_idx = BLOCK_SIZE*(INITIAL_NUM_BLOCKS/2) + BLOCK_SIZE/2 + 1;
    deque->end_idx = deque->start_idx - 1;

    deque->data = malloc(INITIAL_NUM_BLOCKS*sizeof(void *));

    if (deque->data == NULL)
    {
        free(deque);
        return NULL;
    }

    bzero(deque->data, INITIAL_NUM_BLOCKS*sizeof(void *));

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
    unsigned num_blocks_delta = deque->num_blocks/2;
    unsigned new_num_blocks = num_blocks_delta*2 + deque->num_blocks;
    void * new_data = malloc(sizeof(void *)*new_num_blocks);

    if (new_data == NULL)
    {
        return ARC_ERROR;
    }

    memmove((char *)new_data + num_blocks_delta*sizeof(void *), 
           deque->data, deque->num_blocks*sizeof(void *));

    bzero(new_data, num_blocks_delta*sizeof(void *));
    bzero((char *)new_data + (deque->num_blocks + num_blocks_delta)*sizeof(void *),
          num_blocks_delta*sizeof(void *));

    deque->start_idx += num_blocks_delta*BLOCK_SIZE;
    deque->end_idx += num_blocks_delta*BLOCK_SIZE;

    free(deque->data);

    deque->data = new_data;
    deque->num_blocks = new_num_blocks;

    return ARC_SUCCESS;
}

/******************************************************************************/

void * arc_deque2_at(struct arc_deque2 * deque, unsigned idx)
{
    if (idx < deque->size)
    {
        unsigned block_num, block_idx;

        idx = (deque->start_idx + idx) % (deque->num_blocks * BLOCK_SIZE);
        block_num = idx / BLOCK_SIZE;
        block_idx = idx % BLOCK_SIZE;

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

    if(deque->size > 0 && deque->start_idx == 0)
    {
        if (arc_deque2_realloc(deque) != ARC_SUCCESS)
        {
            return ARC_ERROR;
        }
    }

    deque->start_idx--;

    block_num = deque->start_idx / BLOCK_SIZE;
    block_idx = deque->start_idx % BLOCK_SIZE;

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(BLOCK_SIZE*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memmove(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_pop_front(struct arc_deque2 * deque)
{
    if (deque->size > 0)
    {
        deque->start_idx++;
        deque->size--;
    }
}

/******************************************************************************/

int arc_deque2_push_back(struct arc_deque2 * deque, void * data)
{
    unsigned block_num;
    unsigned block_idx;
    void * data_pos;

    if (deque->size > 0 && deque->end_idx == (deque->num_blocks * BLOCK_SIZE - 1))
    {
        if (arc_deque2_realloc(deque) != ARC_SUCCESS)
        {
            return ARC_ERROR;
        }
    }

    deque->end_idx++;

    block_num = deque->end_idx / BLOCK_SIZE;
    block_idx = deque->end_idx % BLOCK_SIZE;

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(BLOCK_SIZE*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memmove(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_pop_back(struct arc_deque2 * deque)
{
    if (deque->size > 0)
    {
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

void arc_deque2_before_begin(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;

    it->node = (void *)((unsigned long)deque->start_idx - 1);
}

/******************************************************************************/

void arc_deque2_begin(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    
    it->node = (void *)((unsigned long)deque->start_idx);
}

/******************************************************************************/

void arc_deque2_end(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    
    it->node = (void *)((unsigned long)deque->end_idx);
}

/******************************************************************************/

void arc_deque2_after_end(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    
    it->node = (void *)((unsigned long)deque->end_idx + 1);
}

/******************************************************************************/

void * arc_deque2_data(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    unsigned long  index = (unsigned long)it->node;

    return arc_deque2_at(deque, (unsigned)index);
}

/******************************************************************************/

int arc_deque2_next(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    unsigned long index = (unsigned long)it->node + 1;

    it->node = (void *)index;

    if (index > deque->end_idx)
    {
        return 0;
    }

    return 1;
}

/******************************************************************************/

int arc_deque2_previous(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    unsigned long index = (unsigned long)it->node - 1;

    it->node = (void *)index;

    if (index < deque->start_idx)
    {
        return 0;
    }

    return 1;
}

/******************************************************************************/
