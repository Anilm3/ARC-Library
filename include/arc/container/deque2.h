/********************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/
/**
 * @file deque2.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Deque2
 *
 * A deque2 is very similar to a singly-linked list but it uses a bit less memory
 * and the operations require less instructions to be performed. The main goal
 * of this redundancy is for performance and experimentation purposes as the 
 * simplicity of the structure provides less instructions per operation thus 
 * making it easier to implement to be lock-free and thread-safe.
 *
 * @see http://en.wikipedia.org/wiki/Deque2_(data_structure)
 */

#ifndef ARC_DEQUE2_H_
#define ARC_DEQUE2_H_

#include <stdlib.h>

/**
 * @typedef arc_deque2_t
 * @brief Deque2 definition
 *
 * The deque2 is defined as a pointer to be used with the creation and destruction
 * functions, direct deque2 allocations are not allowed.
 */
typedef struct arc_deque2 * arc_deque2_t;

/**
 * @brief Creates a new deque2
 *
 * The memory is allocated in the heap and has to be destroyed by the user. The 
 * data size provided has to coincide with the element type size to be used in
 * the container. 
 *
 * @param[in] data_size Size of the data element
 * @return New empty deque2
 * @retval NULL if memory cannot be allocated
 */
arc_deque2_t arc_deque2_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a deque2 
 *
 * @param[in] deque2 Deque2 to perform the operation on
 */
void arc_deque2_destroy(arc_deque2_t deque2);
/**
 * @brief Indexed access to an element of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @param[in] index Position to access
 * @return Data pointer of the first element
 */
void * arc_deque2_at(arc_deque2_t deque2, unsigned index);
/**
 * @brief Adds a new element to the front of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_deque2_push_front(arc_deque2_t deque2, void * data);
/**
 * @brief Removes the first element from the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 */
void arc_deque2_pop_front(arc_deque2_t deque2);
/**
 * @brief Adds a new element to the front of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_deque2_push_back(arc_deque2_t deque2, void * data);
/**
 * @brief Removes the first element from the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 */
void arc_deque2_pop_back(arc_deque2_t deque2);
/**
 * @brief Returns the data of the initial element of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_deque2_front(arc_deque2_t deque2);
/**
 * @brief Returns the data of the last element of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @return Data pointer of the last element
 */
void * arc_deque2_back(arc_deque2_t deque2);
/**
 * @brief Returns whether the deque2 is empty or not
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @retval 0 If the deque2 is not empty
 * @retval 1 If the deque2 is empty
 */
int arc_deque2_empty(arc_deque2_t deque2);
/**
 * @brief Returns the size of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 * @return Size of the deque2
 */
unsigned arc_deque2_size(arc_deque2_t deque2);
/**
 * @brief Clears the contents of the deque2
 *
 * @param[in] deque2 Deque2 to perform the operation on
 */
void arc_deque2_clear(arc_deque2_t deque2);

#endif