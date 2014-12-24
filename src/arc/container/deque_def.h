/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>

#define BLOCK_SIZE 512
#define INITIAL_NUM_BLOCKS 8

/* Container definition */
struct arc_deque
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
