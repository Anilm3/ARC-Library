/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_DARRAY_DEF_H_
#define ARC_DARRAY_DEF_H_

#include <stdlib.h>

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
/**
 * @struct arc_darray_iterator
 * @brief Iterator definition
 */
struct arc_darray_iterator
{
    void * container;
    unsigned long node_idx;
};

int arc_darray_init(struct arc_darray *darray, size_t data_size);
void arc_darray_fini(struct arc_darray *darray);
int arc_darray_iterator_init(struct arc_darray_iterator *it,
                            struct arc_darray *list);
void arc_darray_iterator_fini(struct arc_darray_iterator *it);

#endif
