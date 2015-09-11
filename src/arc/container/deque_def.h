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
 * @brief Reallocates the pointer array effectively increasing the amount of
 *        available memory
 *
 * @param[in] deque Deque to perform the operation on
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
static int arc_deque_realloc(struct arc_deque * deque);
/**
 * @brief Shifts the memory from start to end one place left, both start and end
 *        are included in the shift.
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] start_block_num Block number of the start position
 * @param[in] start_block_idx Block index of the start position
 * @param[in] end_block_num Block number of the end position
 * @param[in] end_block_idx Block index of the end position
 * @retval ARC_SUCCESS If the shift was performed successfully
 */
static int arc_deque_move_left(struct arc_deque * deque,
                               unsigned long start_block_num,
                               unsigned long start_block_idx,
                               unsigned long end_block_num,
                               unsigned long end_block_idx);
/**
 * @brief Shifts the memory from start to end one place right, both start and
 *        end are included in the shift.
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] start_block_num Block number of the start position
 * @param[in] start_block_idx Block index of the start position
 * @param[in] end_block_num Block number of the end position
 * @param[in] end_block_idx Block index of the end position
 * @retval ARC_SUCCESS If the shift was performed successfully
 */
static int arc_deque_move_right(struct arc_deque * deque,
                                unsigned long start_block_num,
                                unsigned long start_block_idx,
                                unsigned long end_block_num,
                                unsigned long end_block_idx);
/**
 * @brief Inserts the data value before the provided position, if memory
 *        has to be shifted it'll be to the left
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] block_num Block number of the position
 * @param[in] block_idx Block index of the position
 * @param[in] data Data to insert in the deque
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
static int arc_deque_insert_node_before_left(struct arc_deque * deque,
                                             unsigned long block_num,
                                             unsigned long block_idx,
                                             void * data);
/**
 * @brief Inserts the data value before the provided position, if memory
 *        has to be shifted it'll be to the right
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] block_num Block number of the position
 * @param[in] block_idx Block index of the position
 * @param[in] data Data to insert in the deque
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
static int arc_deque_insert_node_before_right(struct arc_deque * deque,
                                              unsigned long block_num,
                                              unsigned long block_idx,
                                              void * data);
/**
 * @brief Inserts the data value before the provided position
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] block_num Block number of the position
 * @param[in] block_idx Block index of the position
 * @param[in] data Data to insert in the deque
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
static int arc_deque_insert_node_before(struct arc_deque * deque,
                                        unsigned long block_num,
                                        unsigned long block_idx,
                                        void * data);
/**
 * @brief Erases a the node in the provided position
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] block_num Block number of the position
 * @param[in] block_idx Block index of the position
 */
static void arc_deque_erase_node(struct arc_deque * deque,
                                 unsigned long block_num,
                                 unsigned long block_idx);

#endif
