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
#include <arc/container/darray.h>
#include <arc/common/defines.h>
#include <arc/memory/copy.h>

#include <arc/container/iterator_def.h>

#define INITIAL_BLOCK_SIZE 32
#define GROWTH_FACTOR 2

/* Container definition */
struct arc_darray
{
    size_t size;
    size_t allocated_size;
    size_t data_size;
    void * data;
};

/******************************************************************************/

struct arc_darray * arc_darray_create(size_t data_size)
{
    struct arc_darray * darray = malloc(sizeof(struct arc_darray));

    if (darray == NULL)
    {
        return NULL;
    }

    darray->size = 0;
    darray->data_size = data_size;
    darray->allocated_size = INITIAL_BLOCK_SIZE;

    darray->data = malloc(INITIAL_BLOCK_SIZE*darray->data_size);

    if (darray->data == NULL)
    {
        free(darray);
        return NULL;
    }

    return darray;
}

/******************************************************************************/

void arc_darray_destroy(struct arc_darray * darray)
{
    free(darray->data);
    free(darray);
}

/******************************************************************************/

static int arc_darray_insert_node_before(struct arc_darray * darray,
                                         unsigned long current, void * data)
{
    unsigned long data_to_move = darray->size - current;
    unsigned long data_size = darray->data_size;

    if (darray->size == darray->allocated_size)
    {
        size_t new_size = darray->allocated_size * GROWTH_FACTOR;
        void * ptr = realloc(darray->data, 
                             new_size * darray->data_size);

        if (ptr == NULL)
        {
            return ARC_OUT_OF_MEMORY;
        }

        darray->data = ptr;
        darray->allocated_size *= GROWTH_FACTOR;
    }

    if (data_to_move > 0)
    {
        memmove((char *)darray->data + data_size * (current + 1),
                (char *)darray->data + data_size * current,
                (size_t)(data_to_move * data_size));
    }

    memcpy((char *)darray->data + current * data_size, data, darray->data_size);

    darray->size += 1;

    return ARC_SUCCESS;
}

/******************************************************************************/

static void arc_darray_erase_node(struct arc_darray * darray, 
                                  unsigned long current)
{
    if (darray->size > 0)
    {
        unsigned long data_to_move = darray->size - (current  + 1);

        if (data_to_move > 0)
        {
            unsigned long data_size = darray->data_size;

            memmove((char *)darray->data + data_size * current,
                    (char *)darray->data + data_size * (current + 1),
                    (size_t)(data_to_move * data_size));
        }

        darray->size -= 1;
    }
}

/******************************************************************************/

void * arc_darray_at(struct arc_darray * darray, unsigned long idx)
{
    return (void *)((char *)darray->data + darray->data_size*idx);
}

/******************************************************************************/

int arc_darray_push_front(struct arc_darray * darray, void * data)
{
    return arc_darray_insert_node_before(darray, 0, data);
}

/******************************************************************************/

void arc_darray_pop_front(struct arc_darray * darray)
{
    arc_darray_erase_node(darray, 0);
}

/******************************************************************************/

int arc_darray_push_back(struct arc_darray * darray, void * data)
{
    return arc_darray_insert_node_before(darray, darray->size, data);
}

/******************************************************************************/

void arc_darray_pop_back(struct arc_darray * darray)
{
    arc_darray_erase_node(darray, darray->size - 1);
}

/******************************************************************************/

void * arc_darray_front(struct arc_darray * darray)
{
    if (darray->size == 0)
    {
        return NULL;
    }

    return darray->data;
}

/******************************************************************************/

void * arc_darray_back(struct arc_darray * darray)
{
    if (darray->size == 0)
    {
        return NULL;
    }

    return (char *)darray->data + darray->data_size * (darray->size - 1);
}

/******************************************************************************/

int arc_darray_empty(struct arc_darray * darray)
{
    return darray->size == 0;
}

/******************************************************************************/

unsigned long arc_darray_size(struct arc_darray * darray)
{
    return darray->size;
}

/******************************************************************************/

void arc_darray_clear(struct arc_darray * darray)
{
    darray->size = 0;
}

/******************************************************************************/

void arc_darray_before_begin(struct arc_iterator * it)
{
    it->node_idx = 0;
}

/******************************************************************************/

void arc_darray_begin(struct arc_iterator * it)
{
    it->node_idx = 1;
}

/******************************************************************************/

int arc_darray_position(struct arc_iterator * it, unsigned long idx)
{
    struct arc_darray * darray = it->container;

    if (idx >= darray->size)
    {
        return ARC_ERROR;
    }

    it->node_idx = idx + 1;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_darray_end(struct arc_iterator * it)
{
    struct arc_darray * darray = it->container;
    
    it->node_idx = darray->size;
}

/******************************************************************************/

void arc_darray_after_end(struct arc_iterator * it)
{
    struct arc_darray * darray = it->container;
    
    it->node_idx = darray->size + 1;
}

/******************************************************************************/

int arc_darray_insert_before(struct arc_iterator * it, void * data)
{
    struct arc_darray * darray = it->container;

    if (it->node_idx == 0)
    {
        return ARC_ERROR;
    }

    return arc_darray_insert_node_before(darray, it->node_idx - 1, data);
}

/******************************************************************************/

int arc_darray_insert_after(struct arc_iterator * it, void * data)
{
    struct arc_darray * darray = it->container;

    if (it->node_idx > darray->size)
    {
        return ARC_ERROR;
    }

    return arc_darray_insert_node_before(darray, it->node_idx, data);
}

/******************************************************************************/

void arc_darray_erase(struct arc_iterator * it)
{
    struct arc_darray * darray = it->container;

    if (it->node_idx == 0)
    {
        return;
    }

    arc_darray_erase_node(darray, it->node_idx - 1);
}

/******************************************************************************/

void * arc_darray_data(struct arc_iterator * it)
{
    struct arc_darray * darray = it->container;

    if (it->node_idx == 0)
    {
        return NULL;
    }

    return arc_darray_at(darray, it->node_idx - 1);
}

/******************************************************************************/

int arc_darray_next(struct arc_iterator * it)
{
    struct arc_darray * darray = it->container;

    it->node_idx = (it->node_idx > darray->size ? it->node_idx : 
                                                  it->node_idx + 1);

    return (it->node_idx <= darray->size);
}

/******************************************************************************/

int arc_darray_previous(struct arc_iterator * it)
{
    it->node_idx = (it->node_idx == 0 ? 0 : it->node_idx - 1);

    return (it->node_idx != 0);
}

/******************************************************************************/
