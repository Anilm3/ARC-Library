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
#include <arc/container/deque_def.h>
#include <arc/common/defines.h>
#include <arc/memory/copy.h>

#include <arc/container/iterator_def.h>

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
    deque->block_size = (data_size < BLOCK_SIZE ? BLOCK_SIZE / data_size :
                                                  data_size);
    deque->num_blocks = INITIAL_NUM_BLOCKS;
    deque->start_idx = deque->block_size * (INITIAL_NUM_BLOCKS / 2) +
                       deque->block_size / 2 + 1;
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
    unsigned long num_blocks_delta = deque->num_blocks/2;
    unsigned long new_num_blocks = num_blocks_delta*2 + deque->num_blocks;
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

    deque->start_idx += num_blocks_delta*deque->block_size;
    deque->end_idx += num_blocks_delta*deque->block_size;

    free(deque->data);

    deque->data = new_data;
    deque->num_blocks = new_num_blocks;

    return ARC_SUCCESS;
}

/******************************************************************************/

static int arc_deque_move_left(struct arc_deque * deque,
                               unsigned long start_idx,
                               unsigned long size)
{
    unsigned long block, mem_to_copy, end_idx;
    unsigned long start_block_num, start_block_idx;
    unsigned long end_block_num, end_block_idx;
    void *data_pos, *new_data_pos;

    end_idx = start_idx + size - 1;

    start_block_num = (start_idx - 1) / deque->block_size;
    start_block_idx = (start_idx - 1) % deque->block_size;
    end_block_num = end_idx / deque->block_size;
    end_block_idx = end_idx % deque->block_size;

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
                mem_to_copy = deque->block_size - start_block_idx - 1;
            }

            /* If there is nothing to copy, we don't copy */
            if (mem_to_copy == 0)
            {
                continue;
            }
            /* If the block is full we jump over to a normal copy */
            else if (mem_to_copy < deque->block_size)
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
            deque->data[block - 1] = malloc(deque->block_size*deque->data_size);
        }

        new_data_pos = (char *)deque->data[block - 1] +
                       (deque->block_size - 1) * deque->data_size;
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
                    (deque->block_size - 1) * deque->data_size);
        }
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

static int arc_deque_move_right(struct arc_deque * deque,
                                unsigned long start_idx,
                                unsigned long size)
{
    unsigned long block, mem_to_copy, end_idx;
    unsigned long start_block_num, start_block_idx;
    unsigned long end_block_num, end_block_idx;
    void *data_pos, *new_data_pos;

    end_idx = start_idx + size - 1;

    start_block_num = start_idx / deque->block_size;
    start_block_idx = start_idx % deque->block_size;
    end_block_num = (end_idx + 1) / deque->block_size;
    end_block_idx = (end_idx + 1) % deque->block_size;

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
            else if (mem_to_copy < deque->block_size)
            {
                memmove(new_data_pos, data_pos, mem_to_copy * deque->data_size);

                continue;
            }
        }

        if (deque->data[block + 1] == NULL)
        {
            deque->data[block + 1] = malloc(deque->block_size*deque->data_size);
        }

        new_data_pos = (char *)deque->data[block + 1];
        data_pos = (char *)deque->data[block] +
                       (deque->block_size - 1) * deque->data_size;

        memmove(new_data_pos, data_pos, deque->data_size);

        if (block == start_block_num)
        {
            if((deque->block_size - start_block_idx - 1) > 0)
            {
                new_data_pos = (char *)deque->data[block] +
                               (start_block_idx + 1) * deque->data_size;
                data_pos = (char *)deque->data[block] +
                            start_block_idx * deque->data_size;
                memmove(new_data_pos, data_pos,
                        (deque->block_size - start_block_idx -1) * deque->data_size);
            }
        }
        else
        {
            new_data_pos = (char *)deque->data[block] + deque->data_size;
            data_pos = (char *)deque->data[block];

            memmove(new_data_pos, data_pos,
                    (deque->block_size - 1) * deque->data_size);
        }
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_deque_insert_node_before(struct arc_deque * deque,
                                 unsigned long current, void * data)
{
    unsigned long block_num, block_idx;
    unsigned long left_mem, right_mem;
    void * data_pos;

    if (current < deque->start_idx)
    {
        return ARC_ERROR;
    }

    left_mem = current - deque->start_idx;
    right_mem = (current > deque->end_idx ? 0 : deque->end_idx - current + 1);
    if (left_mem <= right_mem)
    {
        unsigned long size = left_mem;

        current -= deque->start_idx;

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

        current += deque->start_idx;
    }
    else
    {
        unsigned long size = right_mem;

        if (deque->size > 0 &&
            deque->end_idx == (deque->num_blocks * deque->block_size - 1))
        {
            current -= deque->start_idx;
            if (arc_deque_realloc(deque) != ARC_SUCCESS)
            {
                return ARC_OUT_OF_MEMORY;
            }
            current += deque->start_idx;
        }

        if (size > 0)
        {
            arc_deque_move_right(deque, current, size);
        }

        deque->end_idx++;
    }

    block_num = current / deque->block_size;
    block_idx = current % deque->block_size;

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(deque->block_size*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque_erase_node(struct arc_deque * deque,
                          unsigned long current)
{
    if (current < deque->start_idx || current > deque->end_idx)
    {
        return;
    }

    if ((current - deque->start_idx) <= (deque->end_idx - current))
    {
        unsigned long size = current - deque->start_idx;

        if (size > 0)
        {
            arc_deque_move_right(deque, deque->start_idx, size);
        }

        deque->start_idx++;
    }
    else
    {
        unsigned long size = deque->end_idx - current;

        if (size > 0)
        {
            arc_deque_move_left(deque, current + 1, size);
        }

        deque->end_idx--;
    }

    deque->size--;
}

/******************************************************************************/

void * arc_deque_at(struct arc_deque * deque, unsigned long idx)
{
    if (idx < deque->size)
    {
        unsigned long block_num, block_idx;

        idx = (deque->start_idx + idx);/* % (deque->num_blocks * deque->block_size);*/
        block_num = idx / deque->block_size;
        block_idx = idx % deque->block_size;

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
    return arc_deque_insert_node_before(deque, deque->end_idx + 1, data);
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
    unsigned long block_num = deque->start_idx / deque->block_size;
    unsigned long block_idx = deque->start_idx % deque->block_size;

    if (deque->size == 0)
    {
        return NULL;
    }

    return ((char *)deque->data[block_num] + block_idx*deque->data_size);
}

/******************************************************************************/

void * arc_deque_back(struct arc_deque * deque)
{
    unsigned long block_num = deque->end_idx / deque->block_size;
    unsigned long block_idx = deque->end_idx % deque->block_size;

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

unsigned long arc_deque_size(struct arc_deque * deque)
{
    return deque->size;
}

/******************************************************************************/

void arc_deque_clear(struct arc_deque * deque)
{
    deque->size = 0;
    deque->start_idx = deque->block_size*(deque->num_blocks/2) + deque->block_size/2 + 1;
    deque->end_idx = deque->start_idx - 1;
}

/******************************************************************************/

void arc_deque_before_begin(struct arc_iterator * it)
{
    it->node_idx = 0;
}

/******************************************************************************/

void arc_deque_begin(struct arc_iterator * it)
{
    it->node_idx = 1;
}

/******************************************************************************/

int arc_deque_position(struct arc_iterator * it, unsigned long idx)
{
    struct arc_deque * deque = it->container;

    if (idx >= deque->size)
    {
        return ARC_ERROR;
    }

    it->node_idx = idx + 1;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque_end(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;

    it->node_idx = deque->size;
}

/******************************************************************************/

void arc_deque_after_end(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;

    it->node_idx = deque->size + 1;
}

/******************************************************************************/

int arc_deque_insert_before(struct arc_iterator * it, void * data)
{
    struct arc_deque * deque = it->container;

    if (it->node_idx == 0)
    {
        return ARC_ERROR;
    }

    return arc_deque_insert_node_before(deque,
                                        deque->start_idx + it->node_idx - 1,
                                        data);
}

/******************************************************************************/

int arc_deque_insert_after(struct arc_iterator * it, void * data)
{
    struct arc_deque * deque = it->container;

    if (it->node_idx > deque->size)
    {
        return ARC_ERROR;
    }

    return arc_deque_insert_node_before(deque,
                                        deque->start_idx + it->node_idx,
                                        data);
}

/******************************************************************************/

void arc_deque_erase(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;

    if (it->node_idx == 0)
    {
        return;
    }

    arc_deque_erase_node(deque, deque->start_idx + it->node_idx - 1);
}

/******************************************************************************/

void * arc_deque_data(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;

    if (it->node_idx == 0)
    {
        return NULL;
    }

    return arc_deque_at(deque, it->node_idx - 1);
}

/******************************************************************************/

int arc_deque_next(struct arc_iterator * it)
{
    struct arc_deque * deque = it->container;
    unsigned long idx = it->node_idx + 1;

    if (idx > deque->size)
    {
        return 0;
    }

    it->node_idx = idx;

    return 1;
}

/******************************************************************************/

int arc_deque_previous(struct arc_iterator * it)
{
    unsigned long idx = it->node_idx - 1;

    if (idx == 0)
    {
        return 0;
    }

    it->node_idx = idx;

    return 1;
}

/******************************************************************************/
