/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup SList
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 * @ingroup Container
 *
 * @brief Singly-linked list
 *
 * A singly linked list is a structure in which the data is linked together in
 * one direction only. The implementation of the structure is highly based on
 * iterators in order to provide mechanisms to access all the elements in the
 * structure.
 *
 * For more information and examples check the documentation (\ref page_slist).
 *
 * @see http://en.wikipedia.org/wiki/Linked_list#Singly_linked_list
 */

#ifndef ARC_SLIST_H_
#define ARC_SLIST_H_

#include <stdlib.h>
#include <arc/type/function.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_slist_t
 * @brief List definition
 *
 * The list is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_slist * arc_slist_t;
typedef struct arc_slist_iterator * arc_slist_iterator_t;
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
arc_slist_t arc_slist_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a list
 *
 * @param[in] list List to perform the operation on
 */
void arc_slist_destroy(arc_slist_t list);
/**
 * @brief Returns the size of the list
 *
 * @param[in] list List to perform the operation on
 * @return Size of the list
 */
size_t arc_slist_size(arc_slist_t list);
/**
 * @brief Returns whether the list is empty or not
 *
 * @param[in] list List to perform the operation on
 * @retval 0 If the list is not empty
 * @retval 1 If the list is empty
 */
int arc_slist_empty(arc_slist_t list);
/**
 * @brief Clears the contents of the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_slist_clear(arc_slist_t list);
/**
 * @brief Returns the data of the initial element of the list
 *
 * @param[in] list List to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_slist_front(arc_slist_t list);
/**
 * @brief Removes the first element from the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_slist_pop_front(arc_slist_t list);
/**
 * @brief Adds a new element to the front of the list
 *
 * @param[in] list List to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_slist_push_front(arc_slist_t list, void * data);
/**
 * @brief Creates a new iterator
 *
 * The memory is allocated in the heap and has to be destroyed by the user.
 *
 * @param[in] container Container to iterate through
 * @return New iterator for the specified container
 * @retval NULL if memory cannot be allocated
 */
arc_slist_iterator_t arc_slist_iterator_create(arc_slist_t list);
/**
 * @brief Destroys the memory associated to a iterator
 *
 * @param[in] it Iterator to delete
 */
void arc_slist_iterator_destroy(arc_slist_iterator_t it);
/**
 * @brief Sets an iterator to the element before the beginning of the list
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_slist_before_begin(arc_slist_iterator_t it);
/**
 * @brief Sets an iterator to the initial element of the list
 *
 * @param[in] it Iterator
 */
void arc_slist_begin(arc_slist_iterator_t it);
/**
 * @brief Sets an iterator to the element after the end of the list
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_slist_after_end(arc_slist_iterator_t it);
/**
 * @brief Adds an element after the iterator position
 *
 * @param[in] it Iterator
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_slist_insert_after(arc_slist_iterator_t it, void * data);
/**
 * @brief Removes the next node from the list
 *
 * @param[in] it Iterator
 */
void arc_slist_erase_after(arc_slist_iterator_t it);
/**
 * @brief Returns the data associated to the iterator
 *
 * @param[in] it Iterator to perform the operation on
 * @return Data pointer of the node
 */
void * arc_slist_data(arc_slist_iterator_t it);
/**
 * @brief Sets the iterator to the next node in the list
 *
 * @param[in] it Iterator
 * @retval 0 If the element after the end of the list has been reached
 * @retval 1 If the current element is in the list
 */
int arc_slist_next(arc_slist_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif /* ARC_SLIST_H_ */

/** @} */
