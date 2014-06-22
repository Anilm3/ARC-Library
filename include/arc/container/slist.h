/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file slist.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Singly-linked list
 *
 * A singly linked list is a structure in which the data is linked together in
 * one direction only. The implementation of the structure is highly based on
 * iterators (called simply nodes) in order to provide mechanisms to access all 
 * the elements in the structure.
 *
 * @see http://en.wikipedia.org/wiki/Linked_list#Singly_linked_list
 */
 
#ifndef ARC_SLIST_H_
#define ARC_SLIST_H_

#include <stdlib.h> 
#include <arc/container/iterator.h>

/**
 * @typedef arc_slist_t
 * @brief List definition
 *
 * The list is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_slist * arc_slist_t;

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
int arc_slist_size(arc_slist_t list);
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
 * @brief Returns a node to the element before the beginning of the list
 *
 * @param[in] list List to get the node from
 * @return The node before the first node of the list
 */
void arc_slist_before_begin(arc_iterator_t it);
/**
 * @brief Returns a node to the initial element of the list
 *
 * @param[in] list List to get the node from
 * @return First node of the list
 */
void arc_slist_begin(arc_iterator_t it);
/**
 * @brief Returns a node to the element after the end of the list
 *
 * @param[in] list List to get the node from
 * @return The node after the end of the list
 */
void arc_slist_after_end(arc_iterator_t it);
/**
 * @brief Adds an element after the node
 *
 * @param[in] current Reference node 
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_slist_insert_after(arc_iterator_t it, void * data);
/**
 * @brief Removes the next node from the list
 *
 * @param[in] current Reference node
 */
void arc_slist_erase_after(arc_iterator_t it);
/**
 * @brief Returns the data associated to the node
 *
 * @param[in] current Node to perform the operation on
 * @return Data pointer of the node
 */
void * arc_slist_node_data(arc_iterator_t it);
/**
 * @brief Gets the next node in the list
 *
 * @param[in] current Reference node
 * @return New empty list
 */
int arc_slist_node_next(arc_iterator_t it);

#endif