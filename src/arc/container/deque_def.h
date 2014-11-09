/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>

#define BLOCK_SIZE 32
#define INITIAL_NUM_BLOCKS 8

/* Container definition */
struct arc_deque
{
    size_t size;
    unsigned long num_blocks;
    unsigned long start_idx;
    unsigned long end_idx;
    size_t data_size;
    void ** data;
};