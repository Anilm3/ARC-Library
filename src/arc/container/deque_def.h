/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
#ifndef ARC_DEQUE_DEF_H_
#define ARC_DEQUE_DEF_H_

#include <stdlib.h>

#define BLOCK_SIZE 512
#define INITIAL_NUM_BLOCKS 8

/**
 * @struct arc_deque
 * @brief Container definition
 */
struct arc_deque
{
    size_t size; /**< Number of elements in the deque */
    size_t num_blocks; /**< Number of blocks in the pointer array */
    size_t block_size; /**< Size of one block */
    unsigned long start_block_num; /**< Data start block number */
    unsigned long start_block_idx; /**< Data start block index */
    unsigned long end_block_num; /**< Data end block number */
    unsigned long end_block_idx; /**< Data end block index */
    size_t data_size; /**< Size of the data to be inserted */
    void ** data; /**< Pointer array, stores a pointer to each block */
};
/**
 * @struct arc_deque_iterator
 * @brief Iterator definition
 */
struct arc_deque_iterator
{
    void * container;
    void * node_ptr;
    unsigned long node_num;
    unsigned long node_idx;
};

int arc_deque_init(struct arc_deque *deque, size_t data_size);
void arc_deque_fini(struct arc_deque *deque);
int arc_deque_iterator_init(struct arc_deque_iterator *it,
                            struct arc_deque *list);
void arc_deque_iterator_fini(struct arc_deque_iterator *it);

#endif
