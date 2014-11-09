/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file deque.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Deque
 *
 * A deque is very similar to a singly-linked list but it uses a bit less memory
 * and the operations require less instructions to be performed. The main goal
 * of this redundancy is for performance and experimentation purposes as the 
 * simplicity of the structure provides less instructions per operation thus 
 * making it easier to implement to be lock-free and thread-safe.
 *
 * @see http://en.wikipedia.org/wiki/Deque_(data_structure)
 */

#ifndef ARC_DEQUE_H_
#define ARC_DEQUE_H_

#include <stdlib.h>
#include <arc/container/iterator.h>

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @typedef arc_deque_t
 * @brief Deque definition
 *
 * The deque is defined as a pointer to be used with the creation and destruction
 * functions, direct deque allocations are not allowed.
 */
typedef struct arc_deque * arc_deque_t;

/**
 * @brief Creates a new deque
 *
 * The memory is allocated in the heap and has to be destroyed by the user. The 
 * data size provided has to coincide with the element type size to be used in
 * the container. 
 *
 * @param[in] data_size Size of the data element
 * @return New empty deque
 * @retval NULL if memory cannot be allocated
 */
arc_deque_t arc_deque_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a deque 
 *
 * @param[in] deque Deque to perform the operation on
 */
void arc_deque_destroy(arc_deque_t deque);
/**
 * @brief Indexed access to an element of the deque
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] index Position to access
 * @return Data pointer of the first element
 */
void * arc_deque_at(arc_deque_t deque, unsigned long idx);
/**
 * @brief Adds a new element to the front of the deque
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_deque_push_front(arc_deque_t deque, void * data);
/**
 * @brief Removes the first element from the deque
 *
 * @param[in] deque Deque to perform the operation on
 */
void arc_deque_pop_front(arc_deque_t deque);
/**
 * @brief Adds a new element to the front of the deque
 *
 * @param[in] deque Deque to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_deque_push_back(arc_deque_t deque, void * data);
/**
 * @brief Removes the first element from the deque
 *
 * @param[in] deque Deque to perform the operation on
 */
void arc_deque_pop_back(arc_deque_t deque);
/**
 * @brief Returns the data of the initial element of the deque
 *
 * @param[in] deque Deque to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_deque_front(arc_deque_t deque);
/**
 * @brief Returns the data of the last element of the deque
 *
 * @param[in] deque Deque to perform the operation on
 * @return Data pointer of the last element
 */
void * arc_deque_back(arc_deque_t deque);
/**
 * @brief Returns whether the deque is empty or not
 *
 * @param[in] deque Deque to perform the operation on
 * @retval 0 If the deque is not empty
 * @retval 1 If the deque is empty
 */
int arc_deque_empty(arc_deque_t deque);
/**
 * @brief Returns the size of the deque
 *
 * @param[in] deque Deque to perform the operation on
 * @return Size of the deque
 */
unsigned long arc_deque_size(arc_deque_t deque);
/**
 * @brief Clears the contents of the deque
 *
 * @param[in] deque Deque to perform the operation on
 */
void arc_deque_clear(arc_deque_t deque);
/**
 * @brief Sets an iterator to the element before the beginning of the deque
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_deque_before_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the initial element of the deque
 *
 * @param[in] it Iterator
 */
void arc_deque_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the specified element of the deque
 *
 * @param[in] it Iterator
 * @param[in] idx Element index
 * @retval ARC_ERROR If the specified index is out of range
 * @retval ARC_SUCCESS If the iterator was set successfully
 */
int arc_deque_position(arc_iterator_t it, unsigned long idx);
/**
 * @brief Sets an iterator to the last element of the deque
 *
 * @param[in] it Iterator
 */
void arc_deque_end(arc_iterator_t it);
/**
 * @brief Sets an iterator to the element after the end of the deque
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_deque_after_end(arc_iterator_t it);
/**
 * @brief Adds an element before the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_deque_insert_before(arc_iterator_t it, void * data);
/**
 * @brief Adds an element after the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_deque_insert_after(arc_iterator_t it, void * data);
/**
 * @brief Removes the iterator position from the deque
 *
 * @param[in] it Iterator
 */
void arc_deque_erase(arc_iterator_t it);
/**
 * @brief Returns the data associated to the Iterator
 *
 * @param[in] it Iterator
 * @return Data pointer of the node
 */
void * arc_deque_data(arc_iterator_t it);
/**
 * @brief Sets the iterator to the next node in the deque
 *
 * @param[in] it Iterator
 * @retval 0 If the element after the end of the deque has been reached
 * @retval 1 If the current element is in the deque
 */
int arc_deque_next(arc_iterator_t it);
/**
 * @brief Sets the iterator to the previous node in the deque
 *
 * @param[in] it Iterator
 * @retval 0 If the element before the beginning of the deque has been reached
 * @retval 1 If the current element is in the deque
 */
int arc_deque_previous(arc_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif
