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
#include <arc/container/deque.h>
#include <arc/common/defines.h>
#include <arc/memory/copy.h>

#include <arc/container/iterator_def.h>

#define BLOCK_SIZE 32
#define INITIAL_NUM_BLOCKS 8

/* Container definition */
struct arc_deque
{
    unsigned size;
    unsigned num_blocks;
    unsigned start_idx;
    unsigned end_idx;
    size_t data_size;
    void ** data;
};

/******************************************************************************/

struct arc_deque * arc_deque_create(size_t data_size)
{
    struct arc_deque * deque = malloc(sizeof(struct arc_deque));

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

    memset(deque->data, 0, INITIAL_NUM_BLOCKS*sizeof(void *));

    return deque;
}

/******************************************************************************/

void arc_deque_destroy(struct arc_deque * deque)
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

int arc_deque_realloc(struct arc_deque * deque)
{
    unsigned num_blocks_delta = deque->num_blocks/2;
    unsigned new_num_blocks = num_blocks_delta*2 + deque->num_blocks;
    void * new_data = malloc(sizeof(void *)*new_num_blocks);

    if (new_data == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    memmove((char *)new_data + num_blocks_delta*sizeof(void *), 
            deque->data, deque->num_blocks*sizeof(void *));

    memset(new_data, 0, num_blocks_delta*sizeof(void *));
    memset((char *)new_data + (deque->num_blocks + 
          num_blocks_delta) * sizeof(void *), 0,
          num_blocks_delta*sizeof(void *));

    deque->start_idx += num_blocks_delta*BLOCK_SIZE;
    deque->end_idx += num_blocks_delta*BLOCK_SIZE;

    free(deque->data);

    deque->data = new_data;
    deque->num_blocks = new_num_blocks;

    return ARC_SUCCESS;
}

/******************************************************************************/

static int arc_deque_move_left(struct arc_deque * deque,
                               unsigned start_idx, 
                               unsigned size)
{
    unsigned block, mem_to_copy, end_idx;
    unsigned start_block_num, start_block_idx;
    unsigned end_block_num, end_block_idx;
    void *data_pos, *new_data_pos;

    end_idx = start_idx + size - 1;

    start_block_num = (start_idx - 1) / BLOCK_SIZE;
    start_block_idx = (start_idx - 1) % BLOCK_SIZE;
    end_block_num = end_idx / BLOCK_SIZE;
    end_block_idx = end_idx % BLOCK_SIZE;

    for (block = start_block_num; block <= end_block_num; block++)
    {
        if (block == start_block_num)
        {
            if (block == end_block_num)
            {
                mem_to_copy = end_block_idx - start_block_idx;
            }
            else
            {
                mem_to_copy = BLOCK_SIZE - start_block_idx - 1;
            }

            /* If there is nothing to copy, we don't copy */
            if (mem_to_copy == 0)
            {
                continue;
            }
            /* If the block is full we jump over to a normal copy */
            else if (mem_to_copy < BLOCK_SIZE)
            {
                data_pos = (char *)deque->data[block] + 
                            (start_block_idx + 1) * deque->data_size;

                new_data_pos = (char *)deque->data[block] + 
                               start_block_idx * deque->data_size;

                memmove(new_data_pos, data_pos, mem_to_copy * deque->data_size);

                continue;
            }
        }

        if (deque->data[block - 1] == NULL)
        {
            deque->data[block - 1] = malloc(BLOCK_SIZE*deque->data_size);
        }

        new_data_pos = (char *)deque->data[block - 1] + 
                       (BLOCK_SIZE - 1) * deque->data_size;
        data_pos = (char *)deque->data[block];
        memmove(new_data_pos, data_pos, deque->data_size);

        /* What if there is nothing more to copy man, tell me goddamn */
        new_data_pos = (char *)deque->data[block];
        data_pos = (char *)deque->data[block] + deque->data_size;

        if (block == end_block_num)
        {
            if(end_block_idx > 0)
            {
                memmove(new_data_pos, data_pos, 
                        end_block_idx * deque->data_size);
            }
        }
        else
        {
            memmove(new_data_pos, data_pos, 
                    (BLOCK_SIZE - 1) * deque->data_size);
        }
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

static int arc_deque_move_right(struct arc_deque * deque,
                               unsigned start_idx, 
                               unsigned size)
{
    unsigned block, mem_to_copy, end_idx;
    unsigned start_block_num, start_block_idx;
    unsigned end_block_num, end_block_idx;
    void *data_pos, *new_data_pos;

    end_idx = start_idx + size - 1;

    start_block_num = start_idx / BLOCK_SIZE;
    start_block_idx = start_idx % BLOCK_SIZE;
    end_block_num = (end_idx + 1) / BLOCK_SIZE;
    end_block_idx = (end_idx + 1) % BLOCK_SIZE;

    for (block = end_block_num; block >= start_block_num; block--)
    {
        if (block == end_block_num)
        {
            if (block == start_block_num)
            {
                mem_to_copy = end_block_idx - start_block_idx;
                
                data_pos = (char *)deque->data[block] + 
                           start_block_idx * deque->data_size;

                new_data_pos = (char *)deque->data[block] + 
                               (start_block_idx + 1) * deque->data_size;
            }
            else
            {
                mem_to_copy = end_block_idx;

                data_pos = (char *)deque->data[block];

                new_data_pos = (char *)deque->data[block] + deque->data_size;
            }

            /* If there is nothing to copy, we don't copy */
            if (mem_to_copy == 0)
            {
                continue;
            }
            /* If the block is full we jump over to a normal copy */
            else if (mem_to_copy < BLOCK_SIZE)
            {
                memmove(new_data_pos, data_pos, mem_to_copy * deque->data_size);

                continue;
            }
        }

        if (deque->data[block + 1] == NULL)
        {
            deque->data[block + 1] = malloc(BLOCK_SIZE*deque->data_size);
        }

        new_data_pos = (char *)deque->data[block + 1];
        data_pos = (char *)deque->data[block] + 
                       (BLOCK_SIZE - 1) * deque->data_size;

        memmove(new_data_pos, data_pos, deque->data_size);

        if (block == start_block_num)
        {
            if((BLOCK_SIZE - start_block_idx - 1) > 0)
            {
                new_data_pos = (char *)deque->data[block] + 
                               (start_block_idx + 1) * deque->data_size;
                data_pos = (char *)deque->data[block] + 
                            start_block_idx * deque->data_size;
                memmove(new_data_pos, data_pos, 
                        (BLOCK_SIZE - start_block_idx -1) * deque->data_size);
            }
        }
        else
        {
            new_data_pos = (char *)deque->data[block] + deque->data_size;
            data_pos = (char *)deque->data[block];

            memmove(new_data_pos, data_pos, 
                    (BLOCK_SIZE - 1) * deque->data_size);
        }
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_deque_insert_node_before(struct arc_deque * deque,
                                long current, void * data)
{
    unsigned block_num, block_idx;
    void * data_pos;
    unsigned cur_pos = (unsigned)current;

    if (current < deque->start_idx)
    {
        return ARC_ERROR;
    }

    if (((long)cur_pos - deque->start_idx) <= ((long)deque->end_idx - cur_pos))
    {
        unsigned size = cur_pos - deque->start_idx;

        cur_pos -= deque->start_idx;

        if(deque->size > 0 && deque->start_idx == 0)
        {
            if (arc_deque_realloc(deque) != ARC_SUCCESS)
            {
                return ARC_OUT_OF_MEMORY;
            }
        }

        if (size > 0)
        {
            arc_deque_move_left(deque, deque->start_idx, size);
        }

        deque->start_idx--;

        cur_pos += deque->start_idx;
    }
    else
    {
        unsigned size = deque->end_idx - cur_pos + 1;


        if (deque->size > 0 && 
            deque->end_idx == (deque->num_blocks * BLOCK_SIZE - 1))
        {
            cur_pos -= deque->start_idx;
            if (arc_deque_realloc(deque) != ARC_SUCCESS)
            {
                return ARC_OUT_OF_MEMORY;
            }
            cur_pos += deque->start_idx;
        }

        if (size > 0)
        {
            arc_deque_move_right(deque, cur_pos, size);
        }

        deque->end_idx++;
    }

    block_num = cur_pos / BLOCK_SIZE;
    block_idx = cur_pos % BLOCK_SIZE;

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(BLOCK_SIZE*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    arc_memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_deque_insert_node_after(struct arc_deque * deque,
                                 long current, void * data)
{
    if (current > deque->end_idx)
    {
        return ARC_ERROR;
    }

    return arc_deque_insert_node_before(deque, current + 1 , data);
}

/******************************************************************************/

void arc_deque_erase_node(struct arc_deque * deque,
                          long current)
{
    unsigned cur_pos = (unsigned)current;

    if (current < deque->start_idx || current > deque->end_idx)
    {
        return;
    }

    if (((long)cur_pos - deque->start_idx) <= ((long)deque->end_idx - cur_pos))
    {
        unsigned size = cur_pos - deque->start_idx;

        if (size > 0)
        {
            arc_deque_move_right(deque, deque->start_idx, size);
        }

        deque->start_idx++;
    }
    else
    {
        unsigned size = deque->end_idx - cur_pos;

        if (size > 0)
        {
            arc_deque_move_left(deque, cur_pos + 1, size);
        }

        deque->end_idx--;
    }

    deque->size--;
}

/******************************************************************************/

void * arc_deque_at(struct arc_deque * deque, unsigned idx)
{
    if (idx < deque->size)
    {
        unsigned block_num, block_idx;

        idx = (deque->start_idx + idx);/* % (deque->num_blocks * BLOCK_SIZE);*/
        block_num = idx / BLOCK_SIZE;
        block_idx = idx % BLOCK_SIZE;

        return ((char *)deque->data[block_num] + block_idx*deque->data_size);
    }

    return NULL;
}

/******************************************************************************/

int arc_deque_push_front(struct arc_deque * deque, void * data)
{
    return arc_deque_insert_node_before(deque, deque->start_idx, data);
}

/******************************************************************************/

void arc_deque_pop_front(struct arc_deque * deque)
{
    if (deque->size > 0)
    {
        deque->start_idx++;
        deque->size--;
    }
}

/******************************************************************************/

int arc_deque_push_back(struct arc_deque * deque, void * data)
{
    return arc_deque_insert_node_after(deque, deque->end_idx, data);
}

/******************************************************************************/

void arc_deque_pop_back(struct arc_deque * deque)
{
    if (deque->size > 0)
    {
        deque->end_idx--;
        deque->size--;
    }
}

/******************************************************************************/

void * arc_deque_front(struct arc_deque * deque)
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

void * arc_deque_back(struct arc_deque * deque)
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
    deque->size = 0;
    deque->start_idx = BLOCK_SIZE*(deque->num_blocks/2) + BLOCK_SIZE/2 + 1;
    deque->end_idx = deque->start_idx - 1;
}

/******************************************************************************/

void arc_deque_before_begin(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;

    it->node_ptr = (void *)((long)deque->start_idx - 1);
}

/******************************************************************************/

void arc_deque_begin(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    
    it->node_ptr = (void *)((long)deque->start_idx);
}

/******************************************************************************/

int arc_deque_position(struct arc_iterator * it, unsigned idx)
{
    struct arc_deque * deque = it->container;
    
    if (idx > deque->size)
    {
        return ARC_ERROR;
    }

    it->node_ptr = (void *)((long)(deque->start_idx + idx));

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque_end(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    
    it->node_ptr = (void *)((long)deque->end_idx);
}

/******************************************************************************/

void arc_deque_after_end(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    
    it->node_ptr = (void *)((long)deque->end_idx + 1);
}

/******************************************************************************/

int arc_deque_insert_before(struct arc_iterator * it, void * data)
{
    struct arc_deque * deque = it->container;
    long idx = (long)it->node_ptr;

    return arc_deque_insert_node_before(deque, idx , data);
}

/******************************************************************************/

int arc_deque_insert_after(struct arc_iterator * it, void * data)
{
    struct arc_deque * deque = it->container;
    long idx = (long)it->node_ptr;

    return arc_deque_insert_node_after(deque, idx , data);
}

/******************************************************************************/

void arc_deque_erase(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    long idx = (long)it->node_ptr;

    arc_deque_erase_node(deque, idx);
}

/******************************************************************************/

void * arc_deque_data(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    long idx = ((long)it->node_ptr) - deque->start_idx;

    return arc_deque_at(deque, (unsigned)idx);
}

/******************************************************************************/

int arc_deque_next(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    long idx = (long)it->node_ptr + 1;

    if (idx > deque->end_idx)
    {
        return 0;
    }

    it->node_ptr = (void *)idx;

    return 1;
}

/******************************************************************************/

int arc_deque_previous(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    long idx = (long)it->node_ptr - 1;

    if (idx < deque->start_idx)
    {
        return 0;
    }

    it->node_ptr = (void *)idx;

    return 1;
}

/******************************************************************************/
