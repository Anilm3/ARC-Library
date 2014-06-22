/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file dlist2.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
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
 
#ifndef ARC_DLIST2_H_
#define ARC_DLIST2_H_

#include <stdlib.h> 
#include <arc/container/iterator.h>

/**
 * @typedef arc_dlist2_t
 * @brief List definition
 *
 * The list is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_dlist2 * arc_dlist2_t;

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
arc_dlist2_t arc_dlist2_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a list 
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist2_destroy(arc_dlist2_t list);
/**
 * @brief Returns the size of the list
 *
 * @param[in] list List to perform the operation on
 * @return Size of the list
 */
int arc_dlist2_size(arc_dlist2_t list);
/**
 * @brief Returns whether the list is empty or not
 *
 * @param[in] list List to perform the operation on
 * @retval 0 If the list is not empty
 * @retval 1 If the list is empty
 */
int arc_dlist2_empty(arc_dlist2_t list);
/**
 * @brief Clears the contents of the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist2_clear(arc_dlist2_t list);
/**
 * @brief Returns the data of the initial element of the list
 *
 * @param[in] list List to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_dlist2_front(arc_dlist2_t list);
/**
 * @brief Removes the first element from the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist2_pop_front(arc_dlist2_t list);
/**
 * @brief Adds a new element to the front of the list
 *
 * @param[in] list List to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist2_push_front(arc_dlist2_t list, void * data);
/**
 * @brief Returns the data of the last element of the list
 *
 * @param[in] list List to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_dlist2_back(arc_dlist2_t list);
/**
 * @brief Removes the last element from the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_dlist2_pop_back(arc_dlist2_t list);
/**
 * @brief Adds a new element to the back of the list
 *
 * @param[in] list List to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist2_push_back(arc_dlist2_t list, void * data);
/**
 * @brief Returns a node to the element before the beginning of the list
 *
 * @param[in] list List to get the node from
 * @return The node before the first node of the list
 */
void arc_dlist2_before_begin(arc_iterator_t it);
/**
 * @brief Returns a node to the initial element of the list
 *
 * @param[in] list List to get the node from
 * @return First node of the list
 */
void arc_dlist2_begin(arc_iterator_t it);
/**
 * @brief Returns a node to the end element of the list
 *
 * @param[in] list List to get the node from
 * @return First node of the list
 */
void arc_dlist2_end(arc_iterator_t it);
/**
 * @brief Returns a node to the element after the end of the list
 *
 * @param[in] list List to get the node from
 * @return The node after the end of the list
 */
void arc_dlist2_after_end(arc_iterator_t it);
/**
 * @brief Adds an element before the node
 *
 * @param[in] current Reference node 
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist2_insert_before(arc_iterator_t current, void * data);
/**
 * @brief Adds an element after the node
 *
 * @param[in] current Reference node 
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_dlist2_insert_after(arc_iterator_t current, void * data);
/**
 * @brief Removes the next node from the list
 *
 * @param[in] current Reference node
 */
void arc_dlist2_erase(arc_iterator_t current);
/**
 * @brief Returns the data associated to the node
 *
 * @param[in] current Node to perform the operation on
 * @return Data pointer of the node
 */
void * arc_dlist2_node_data(arc_iterator_t current);
/**
 * @brief Gets the next node in the list
 *
 * @param[in] current Reference node
 * @return New empty list
 */
int arc_dlist2_node_next(arc_iterator_t current);
/**
 * @brief Gets the previous node in the list
 *
 * @param[in] current Reference node
 * @return New empty list
 */
int arc_dlist2_node_previous(arc_iterator_t current);

#endif