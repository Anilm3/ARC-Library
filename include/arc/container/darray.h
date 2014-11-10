/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file darray.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Dynamic Array
 *
 * A darray is very similar to a singly-linked list but it uses a bit less memory
 * and the operations require less instructions to be performed. The main goal
 * of this redundancy is for performance and experimentation purposes as the 
 * simplicity of the structure provides less instructions per operation thus 
 * making it easier to implement to be lock-free and thread-safe.
 *
 * @see http://en.wikipedia.org/wiki/Dynamic_array
 */

#ifndef ARC_DARRAY_H_
#define ARC_DARRAY_H_

#include <stdlib.h>
#include <arc/container/iterator.h>

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @typedef arc_darray_t
 * @brief Dynamic Array definition
 *
 * The darray is defined as a pointer to be used with the creation and destruction
 * functions, direct darray allocations are not allowed.
 */
typedef struct arc_darray * arc_darray_t;

/**
 * @brief Creates a new darray
 *
 * The memory is allocated in the heap and has to be destroyed by the user. The 
 * data size provided has to coincide with the element type size to be used in
 * the container. 
 *
 * @param[in] data_size Size of the data element
 * @return New empty darray
 * @retval NULL if memory cannot be allocated
 */
arc_darray_t arc_darray_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a darray 
 *
 * @param[in] darray Dynamic Array to perform the operation on
 */
void arc_darray_destroy(arc_darray_t darray);
/**
 * @brief Indexed access to an element of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @param[in] idx Position to access
 * @return Data pointer of the first element
 */
void * arc_darray_at(arc_darray_t darray, unsigned long idx);
/**
 * @brief Adds a new element to the front of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_darray_push_front(arc_darray_t darray, void * data);
/**
 * @brief Removes the first element from the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 */
void arc_darray_pop_front(arc_darray_t darray);
/**
 * @brief Adds a new element to the front of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_darray_push_back(arc_darray_t darray, void * data);
/**
 * @brief Removes the first element from the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 */
void arc_darray_pop_back(arc_darray_t darray);
/**
 * @brief Returns the data of the initial element of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_darray_front(arc_darray_t darray);
/**
 * @brief Returns the data of the last element of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @return Data pointer of the last element
 */
void * arc_darray_back(arc_darray_t darray);
/**
 * @brief Returns whether the darray is empty or not
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @retval 0 If the darray is not empty
 * @retval 1 If the darray is empty
 */
int arc_darray_empty(arc_darray_t darray);
/**
 * @brief Returns the size of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 * @return Size of the darray
 */
size_t arc_darray_size(arc_darray_t darray);
/**
 * @brief Clears the contents of the darray
 *
 * @param[in] darray Dynamic Array to perform the operation on
 */
void arc_darray_clear(arc_darray_t darray);
/**
 * @brief Sets an iterator to the element before the beginning of the darray
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_darray_before_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the initial element of the darray
 *
 * @param[in] it Iterator
 */
void arc_darray_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the specified element of the darray
 *
 * @param[in] it Iterator
 * @param[in] idx Element index
 * @retval ARC_ERROR If the specified index is out of range
 * @retval ARC_SUCCESS If the iterator was set successfully
 */
int arc_darray_position(arc_iterator_t it, unsigned long idx);
/**
 * @brief Sets an iterator to the last element of the darray
 *
 * @param[in] it Iterator
 */
void arc_darray_end(arc_iterator_t it);
/**
 * @brief Sets an iterator to the element after the end of the darray
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_darray_after_end(arc_iterator_t it);
/**
 * @brief Adds an element before the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_darray_insert_before(arc_iterator_t it, void * data);
/**
 * @brief Adds an element after the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_darray_insert_after(arc_iterator_t it, void * data);
/**
 * @brief Removes the iterator position from the darray
 *
 * @param[in] it Iterator
 */
void arc_darray_erase(arc_iterator_t it);
/**
 * @brief Returns the data associated to the Iterator
 *
 * @param[in] it Iterator
 * @return Data pointer of the node
 */
void * arc_darray_data(arc_iterator_t it);
/**
 * @brief Sets the iterator to the next node in the darray
 *
 * @param[in] it Iterator
 * @retval 0 If the element after the end of the darray has been reached
 * @retval 1 If the current element is in the darray
 */
int arc_darray_next(arc_iterator_t it);
/**
 * @brief Sets the iterator to the previous node in the darray
 *
 * @param[in] it Iterator
 * @retval 0 If the element before the beginning of the darray has been reached
 * @retval 1 If the current element is in the darray
 */
int arc_darray_previous(arc_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif
