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
    unsigned size;
    unsigned allocated_size;
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

void * arc_darray_at(struct arc_darray * darray, unsigned idx)
{
    return (void *)((char *)darray->data + darray->data_size*idx);
}

/******************************************************************************/

int arc_darray_push_front(struct arc_darray * darray, void * data)
{
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
    
    memmove((char *)darray->data + darray->data_size,
            darray->data, darray->data_size * darray->size);

    memcpy(darray->data, data, darray->data_size);

    darray->size += 1;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_darray_pop_front(struct arc_darray * darray)
{
    if (darray->size > 0)
    {
        memmove(darray->data, (char *)darray->data + darray->data_size,
                darray->data_size * darray->size);
        darray->size -= 1;
    }
}

/******************************************************************************/

int arc_darray_push_back(struct arc_darray * darray, void * data)
{
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

    memcpy((char *)darray->data + darray->data_size * darray->size,
            data, darray->data_size);

    darray->size += 1;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_darray_pop_back(struct arc_darray * darray)
{
    if (darray->size > 0)
    {
        darray->size -= 1;
    }
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

unsigned arc_darray_size(struct arc_darray * darray)
{
    return darray->size;
}

/******************************************************************************

void arc_darray_clear(struct arc_darray * darray)
{

}

******************************************************************************

void arc_darray_before_begin(struct arc_iterator * it)
{

}

******************************************************************************

void arc_darray_begin(struct arc_iterator * it)
{

}

******************************************************************************

void arc_darray_end(struct arc_iterator * it)
{

}

******************************************************************************

void arc_darray_after_end(struct arc_iterator * it)
{

}

******************************************************************************

int arc_darray_insert_before(struct arc_iterator * it, void * data)
{

}

******************************************************************************

int arc_darray_insert_after(struct arc_iterator * it, void * data)
{

}

******************************************************************************

void arc_darray_erase(struct arc_iterator * it)
{

}

******************************************************************************

void * arc_darray_data(struct arc_iterator * it)
{

}

******************************************************************************

int arc_darray_next(struct arc_iterator * it)
{

}

******************************************************************************

int arc_darray_previous(struct arc_iterator * it)
{

}

******************************************************************************/
