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

#include <arc/container/iterator_def.h>

#define BLOCK_SIZE 512
#define INITIAL_NUM_BLOCKS 8

/* Container definition */
struct arc_deque2
{
    size_t size;
    size_t num_blocks;
    size_t block_size;
    unsigned long start_block_num;
    unsigned long start_block_idx;
    unsigned long end_block_num;
    unsigned long end_block_idx;
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
    deque->block_size = (data_size < BLOCK_SIZE ? BLOCK_SIZE / data_size :
                                                  data_size);
    deque->num_blocks = INITIAL_NUM_BLOCKS;
    deque->start_block_num = INITIAL_NUM_BLOCKS / 2;
    deque->start_block_idx = deque->block_size / 2 + 1;
    deque->end_block_num = INITIAL_NUM_BLOCKS / 2;
    deque->end_block_idx = deque->start_block_idx - 1;

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

static int arc_deque2_realloc(struct arc_deque2 * deque)
{
    unsigned long num_blocks_delta = deque->num_blocks/2;
    unsigned long new_num_blocks = num_blocks_delta*2 + deque->num_blocks;
    void * new_data = malloc(sizeof(void *)*new_num_blocks);

    if (new_data == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    memcpy((char *)new_data + num_blocks_delta * sizeof(void *),
            deque->data, deque->num_blocks * sizeof(void *));

    memset(new_data, 0, num_blocks_delta * sizeof(void *));
    memset((char *)new_data + (deque->num_blocks +
          num_blocks_delta) * sizeof(void *), 0,
          num_blocks_delta * sizeof(void *));

    deque->start_block_num += num_blocks_delta;
    deque->end_block_num += num_blocks_delta;

    free(deque->data);

    deque->data = new_data;
    deque->num_blocks = new_num_blocks;

    return ARC_SUCCESS;
}

/******************************************************************************/
/*
  [start, end]
*/
static int arc_deque2_move_left(struct arc_deque2 * deque,
                               unsigned long start_block_num,
                               unsigned long start_block_idx,
                               unsigned long end_block_num,
                               unsigned long end_block_idx)
{
    unsigned long block, mem_to_copy;
    void *data_pos, *new_data_pos;

    if (start_block_idx == 0)
    {
        start_block_idx = deque->block_size - 1;
        start_block_num--;
    }
    else
    {
        start_block_idx--;
    }

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
/*
  [start, end]
*/
static int arc_deque2_move_right(struct arc_deque2 * deque,
                                unsigned long start_block_num,
                                unsigned long start_block_idx,
                                unsigned long end_block_num,
                                unsigned long end_block_idx)
{
    unsigned long block, mem_to_copy;
    void *data_pos, *new_data_pos;

    if (end_block_idx == (deque->block_size - 1))
    {
        end_block_idx = 0;
        end_block_num++;
    }
    else
    {
        end_block_idx++;
    }

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

int arc_deque2_insert_node_before_left(struct arc_deque2 * deque,
                                       unsigned long block_num,
                                       unsigned long block_idx,
                                       void * data)
{
    void * data_pos;

    if (deque->start_block_num != block_num ||
        deque->start_block_idx != block_idx)
    {
        if (block_idx == 0)
        {
            block_num--;
            block_idx = deque->block_size - 1;
        }
        else
        {
            block_idx--;
        }

        arc_deque2_move_left(deque,
                             deque->start_block_num,
                             deque->start_block_idx,
                             block_num, block_idx);
    }
    else
    {
        if (block_idx == 0)
        {
            block_num--;
            block_idx = deque->block_size - 1;
        }
        else
        {
            block_idx--;
        }
    }

    if (deque->start_block_idx == 0)
    {
        deque->start_block_num--;
        deque->start_block_idx = deque->block_size - 1;
    }
    else
    {
        deque->start_block_idx--;
    }

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(deque->block_size*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    if(deque->start_block_num == 0 &&
       deque->start_block_idx == 0)
    {
        if (arc_deque2_realloc(deque) != ARC_SUCCESS)
        {
            return ARC_OUT_OF_MEMORY;
        }
    }

    return ARC_SUCCESS;
}


int arc_deque2_insert_node_before_right(struct arc_deque2 * deque,
                                        unsigned long block_num,
                                        unsigned long block_idx,
                                        void * data)
{
    void * data_pos;

    if (block_num < deque->end_block_num ||
        (block_num == deque->end_block_num &&
         block_idx <= deque->end_block_idx))
    {
        arc_deque2_move_right(deque, block_num, block_idx,
                              deque->end_block_num, deque->end_block_idx);
    }

    deque->end_block_idx++;

    if (deque->end_block_idx == deque->block_size)
    {
        deque->end_block_idx = 0;
        deque->end_block_num++;
    }

    if (deque->data[block_num] == NULL)
    {
        deque->data[block_num] = malloc(deque->block_size*deque->data_size);
    }

    data_pos = ((char *)deque->data[block_num] + block_idx*deque->data_size);

    memcpy(data_pos, data, deque->data_size);

    deque->size++;

    if (deque->end_block_num == (deque->num_blocks - 1) &&
        deque->end_block_idx == (deque->block_size - 1))
    {
        if (arc_deque2_realloc(deque) != ARC_SUCCESS)
        {
            return ARC_OUT_OF_MEMORY;
        }
    }

    return ARC_SUCCESS;
}

int arc_deque2_insert_node_before(struct arc_deque2 * deque,
                                 unsigned long block_num,
                                 unsigned long block_idx,
                                 void * data)
{
    unsigned long block, end, start;
    unsigned long left_mem, right_mem;

    /** This is too darn slow? */
    start = deque->start_block_num * deque->block_size + deque->start_block_idx;
    end = deque->end_block_num * deque->block_size + deque->end_block_idx;
    block = block_num * deque->block_size + block_idx;

    left_mem = block - start;
    right_mem = (block > end ? 0 : end - block_num + 1);

    if (left_mem <= right_mem)
    {
        return arc_deque2_insert_node_before_left(deque, block_num,
                                                  block_idx, data);
    }
    else
    {
        return arc_deque2_insert_node_before_right(deque, block_num,
                                                   block_idx, data);
    }
}

/******************************************************************************/

void arc_deque2_erase_node(struct arc_deque2 * deque,
                           unsigned long block_num,
                           unsigned long block_idx)
{
    unsigned long block, end, start;
    unsigned long left_mem, right_mem;

    /** This is too darn slow? */
    start = deque->start_block_num * deque->block_size + deque->start_block_idx;
    end = deque->end_block_num * deque->block_size + deque->end_block_idx;
    block = block_num * deque->block_size + block_idx;
    /*printf("%lu %lu %lu  ->  ", start, end, block);*/
    left_mem = block - start;
    right_mem = (block > end ? 0 : end - block + 1);
    /*printf("%lu %lu\n", left_mem, right_mem);*/
    if (left_mem <= right_mem)
    {
        /*printf("Left\n");*/
        if (left_mem > 0)
        {
            if (block_idx == 0)
            {
                block_num--;
                block_idx = deque->block_size - 1;
            }
            else
            {
                block_idx--;
            }

            arc_deque2_move_right(deque,
                                  deque->start_block_num,
                                  deque->start_block_idx,
                                  block_num, block_idx);
        }

        deque->start_block_idx++;

        if (deque->start_block_idx == deque->block_size)
        {
            deque->start_block_idx = 0;
            deque->start_block_num++;
        }
    }
    else
    {
        /*printf("Right\n");*/
        if (right_mem > 0)
        {
            block_idx++;
            if (block_idx == deque->block_size)
            {
                block_num++;
                block_idx = 0;
            }

            arc_deque2_move_left(deque,
                                 block_num, block_idx,
                                 deque->end_block_num,
                                 deque->end_block_idx);
        }

        if (deque->end_block_idx == 0)
        {
            deque->end_block_num--;
            deque->end_block_idx = deque->block_size - 1;
        }
        else
        {
            deque->end_block_idx--;
        }
    }

    deque->size--;
}


/******************************************************************************/

void * arc_deque2_at(struct arc_deque2 * deque, unsigned long idx)
{
    if (idx < deque->size)
    {
        unsigned long block_num, block_idx;

        block_num = deque->start_block_num + idx / deque->block_size;
        block_idx = deque->start_block_idx + idx % deque->block_size;

        if (block_idx >= deque->block_size)
        {
            block_idx -= deque->block_size;
            block_num++;
        }

        return ((char *)deque->data[block_num] + block_idx*deque->data_size);
    }

    return NULL;
}

/******************************************************************************/

int arc_deque2_push_front(struct arc_deque2 * deque, void * data)
{
    return arc_deque2_insert_node_before_left(deque,
                                              deque->start_block_num,
                                              deque->start_block_idx,
                                              data);
}

/******************************************************************************/

void arc_deque2_pop_front(struct arc_deque2 * deque)
{
    if (deque->size > 0)
    {
        deque->start_block_idx++;
        if (deque->start_block_idx == deque->block_size)
        {
            deque->start_block_num++;
            deque->start_block_idx = 0;
        }

        deque->size--;
    }
}

/******************************************************************************/

int arc_deque2_push_back(struct arc_deque2 * deque, void * data)
{
    unsigned long end_num = deque->end_block_num;
    unsigned long end_idx = deque->end_block_idx + 1;

    if (end_idx == deque->block_size)
    {
        end_idx = 0;
        end_num += 1;
    }

    return arc_deque2_insert_node_before_right(deque,
                                               end_num,
                                               end_idx,
                                               data);
}

/******************************************************************************/

void arc_deque2_pop_back(struct arc_deque2 * deque)
{
    if (deque->size > 0)
    {
        if (deque->end_block_idx == 0)
        {
            deque->end_block_idx = deque->block_size - 1;
            deque->end_block_num--;
        }
        else
        {
            deque->end_block_idx--;
        }

        deque->size--;
    }
}

/******************************************************************************/

void * arc_deque2_front(struct arc_deque2 * deque)
{
    unsigned long block_num = deque->start_block_num;
    unsigned long block_idx = deque->start_block_idx;

    if (deque->size == 0)
    {
        return NULL;
    }

    return ((char *)deque->data[block_num] + block_idx*deque->data_size);
}

/******************************************************************************/

void * arc_deque2_back(struct arc_deque2 * deque)
{
    unsigned long block_num = deque->end_block_num;
    unsigned long block_idx = deque->end_block_idx;

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

unsigned long arc_deque2_size(struct arc_deque2 * deque)
{
    return deque->size;
}

/******************************************************************************/

void arc_deque2_clear(struct arc_deque2 * deque)
{
    deque->size = 0;
    deque->start_block_num = deque->num_blocks / 2;
    deque->start_block_idx = deque->block_size / 2 + 1;
    deque->end_block_num = deque->num_blocks / 2;
    deque->end_block_idx = deque->start_block_idx - 1;
}

/******************************************************************************/

void arc_deque2_before_begin(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    it->node_num = deque->start_block_num;
    it->node_idx = deque->start_block_idx;

    if (it->node_idx == 0)
    {
        it->node_num--;
        it->node_idx = deque->block_size - 1;
    }
    else
    {
        it->node_idx--;
    }
}

/******************************************************************************/

void arc_deque2_begin(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    it->node_num = deque->start_block_num;
    it->node_idx = deque->start_block_idx;
}

/******************************************************************************/

int arc_deque2_position(struct arc_iterator * it, unsigned long idx)
{
    struct arc_deque2 * deque = it->container;

    if (idx >= deque->size)
    {
        return ARC_ERROR;
    }

    it->node_num = deque->start_block_num + idx / deque->block_size;
    it->node_idx = deque->start_block_idx + idx % deque->block_size;

    if (it->node_idx >= deque->block_size)
    {
        it->node_idx -= deque->block_size;
        it->node_num++;
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_deque2_end(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;

    it->node_num = deque->end_block_num;
    it->node_idx = deque->end_block_idx;
}

/******************************************************************************/

void arc_deque2_after_end(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;

    it->node_num = deque->end_block_num;
    it->node_idx = deque->end_block_idx + 1;

    if (it->node_idx >= deque->block_size)
    {
        it->node_idx -= deque->block_size;
        it->node_num++;
    }
}

/******************************************************************************/

int arc_deque2_insert_before(struct arc_iterator * it, void * data)
{
    struct arc_deque2 * deque = it->container;

    if (it->node_num < deque->start_block_num ||
        (it->node_num == deque->start_block_num &&
         it->node_idx < deque->start_block_idx))
    {
        return ARC_ERROR;
    }

    return arc_deque2_insert_node_before(deque,
                                         it->node_num,
                                         it->node_idx,
                                         data);
}

/******************************************************************************/

int arc_deque2_insert_after(struct arc_iterator * it, void * data)
{
    struct arc_deque2 * deque = it->container;
    unsigned long block_num = it->node_num;
    unsigned long block_idx = it->node_idx + 1;

    if (it->node_num > deque->end_block_num ||
        (it->node_num == deque->end_block_num &&
         it->node_idx > deque->end_block_idx))
    {
        return ARC_ERROR;
    }

    if (block_idx == deque->block_size)
    {
        block_num++;
        block_idx = 0;
    }

    return arc_deque2_insert_node_before(deque, block_num, block_idx, data);
}
/******************************************************************************/

void arc_deque2_erase(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;

   if ((it->node_num > deque->end_block_num ||
        (it->node_num == deque->end_block_num &&
         it->node_idx > deque->end_block_idx)) ||
       (it->node_num < deque->start_block_num ||
        (it->node_num == deque->start_block_num &&
         it->node_idx < deque->start_block_idx)))
    {
        return;
    }

    arc_deque2_erase_node(deque, it->node_num, it->node_idx);
}

/******************************************************************************/

void * arc_deque2_data(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;

    return ((char *)deque->data[it->node_num] + it->node_idx*deque->data_size);
}

/******************************************************************************/

int arc_deque2_next(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    unsigned long node_num = it->node_num = it->node_num;
    unsigned long node_idx = it->node_idx = it->node_idx;

    node_idx++;

    if (node_idx == deque->block_size)
    {
        node_num++;
        node_idx = 0;
    }

    if ((node_num == deque->end_block_num &&
         node_idx > deque->end_block_idx) ||
        node_num > deque->end_block_num)
    {
        return 0;
    }

    it->node_num = node_num;
    it->node_idx = node_idx;

    return 1;
}

/******************************************************************************/

int arc_deque2_previous(struct arc_iterator * it)
{
    struct arc_deque2 * deque = it->container;
    unsigned long node_num = it->node_num = it->node_num;
    unsigned long node_idx = it->node_idx = it->node_idx;

    if (node_idx == 0)
    {
        node_num--;
        node_idx = deque->block_size - 1;
    }
    else
    {
        node_idx--;
    }

    if ((node_num == deque->start_block_num &&
         node_idx < deque->start_block_idx) ||
        node_num < deque->start_block_num)
    {
        return 0;
    }

    it->node_num = node_num;
    it->node_idx = node_idx;

    return 1;
}

/******************************************************************************/
