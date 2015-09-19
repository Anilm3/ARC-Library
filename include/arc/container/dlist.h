/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup DList
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 * @ingroup Container
 *
 * @brief Doubly-linked list
 *
 * A double linked list is a structure in which the data is linked together in
 * both directions. The implementation of the structure is highly based on
 * iterators (called simply nodes) in order to provide mechanisms to access all
 * the elements in the structure.
 *
 * @see http://en.wikipedia.org/wiki/Doubly_linked_list
 */

#ifndef ARC_DLIST_H_
#define ARC_DLIST_H_

#include <stdlib.h>
#include <arc/container/iterator.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_dlist_t
 * @brief List definition
 *
 * The list is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_dlist * arc_dlist_t;

/**
 * @brief Creates a new list
 *
 * The memory is allocated in the heap and has to be destroyed by the user. The
 * data size provided has to coincide with the element type size to be used in
 * the container.
 *
 * @param[in] data_size Size of the data element
 * @return New empty list
 * @retval NULL if memory cannot be allocated
 */
arc_dlist_t arc_dlist_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist_destroy(arc_dlist_t list);
/**
 * @brief Returns the size of the list
 *
 * @param[in] list List to perform the operation on
 * @return Size of the list
 */
size_t arc_dlist_size(arc_dlist_t list);
/**
 * @brief Returns whether the list is empty or not
 *
 * @param[in] list List to perform the operation on
 * @retval 0 If the list is not empty
 * @retval 1 If the list is empty
 */
int arc_dlist_empty(arc_dlist_t list);
/**
 * @brief Clears the contents of the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist_clear(arc_dlist_t list);
/**
 * @brief Returns the data of the initial element of the list
 *
 * @param[in] list List to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_dlist_front(arc_dlist_t list);
/**
 * @brief Removes the first element from the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist_pop_front(arc_dlist_t list);
/**
 * @brief Adds a new element to the front of the list
 *
 * @param[in] list List to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist_push_front(arc_dlist_t list, void * data);
/**
 * @brief Returns the data of the last element of the list
 *
 * @param[in] list List to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_dlist_back(arc_dlist_t list);
/**
 * @brief Removes the last element from the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist_pop_back(arc_dlist_t list);
/**
 * @brief Adds a new element to the back of the list
 *
 * @param[in] list List to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist_push_back(arc_dlist_t list, void * data);
/**
 * @brief Sets an iterator to the element before the beginning of the list
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_dlist_before_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the initial element of the list
 *
 * @param[in] it Iterator
 */
void arc_dlist_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the last element of the list
 *
 * @param[in] it Iterator
 */
void arc_dlist_end(arc_iterator_t it);
/**
 * @brief Sets an iterator to the element after the end of the list
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_dlist_after_end(arc_iterator_t it);
/**
 * @brief Adds an element before the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist_insert_before(arc_iterator_t it, void * data);
/**
 * @brief Adds an element after the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist_insert_after(arc_iterator_t it, void * data);
/**
 * @brief Removes the iterator position from the list
 *
 * @param[in] it Iterator
 */
void arc_dlist_erase(arc_iterator_t it);
/**
 * @brief Returns the data associated to the Iterator
 *
 * @param[in] it Iterator
 * @return Data pointer of the node
 */
void * arc_dlist_data(arc_iterator_t it);
/**
 * @brief Sets the iterator to the next node in the list
 *
 * @param[in] it Iterator
 * @retval 0 If the element after the end of the list has been reached
 * @retval 1 If the current element is in the list
 */
int arc_dlist_next(arc_iterator_t it);
/**
 * @brief Sets the iterator to the previous node in the list
 *
 * @param[in] it Iterator
 * @retval 0 If the element before the beginning of the list has been reached
 * @retval 1 If the current element is in the list
 */
int arc_dlist_previous(arc_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif /* ARC_DLIST_H_ */

/** @} */
