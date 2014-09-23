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

#define BLOCK_SIZE 32

/* Container definition */
struct arc_darray
{
    unsigned size;
    size_t data_size;
    void * data;
};

/******************************************************************************

struct arc_darray * arc_darray_create(size_t data_size)
{

}

******************************************************************************

void arc_darray_destroy(struct arc_darray * darray)
{

}

******************************************************************************

void * arc_darray_at(struct arc_darray * darray, unsigned idx)
{

}

******************************************************************************

int arc_darray_push_front(struct arc_darray * darray, void * data)
{

}

******************************************************************************

void arc_darray_pop_front(struct arc_darray * darray)
{

}

******************************************************************************

int arc_darray_push_back(struct arc_darray * darray, void * data)
{

}

******************************************************************************

void arc_darray_pop_back(struct arc_darray * darray)
{

}

******************************************************************************

void * arc_darray_front(struct arc_darray * darray)
{

}

******************************************************************************

void * arc_darray_back(struct arc_darray * darray)
{

}

******************************************************************************

int arc_darray_empty(struct arc_darray * darray)
{

}

******************************************************************************

unsigned arc_darray_size(struct arc_darray * darray)
{

}

******************************************************************************

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
