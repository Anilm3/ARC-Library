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

#endif
