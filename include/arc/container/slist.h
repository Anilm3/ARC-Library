/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @author Anil M. Mahtani Mirchandani
 * @file slist.h
 */
 
#ifndef ARC_SLIST_H_
#define ARC_SLIST_H_

#include <stdlib.h> 

/**
 * @typedef arc_slist_t
 * @brief List definition
 *
 * The list is defined as a pointer to be used with the creation and destruction
 * functions, stack allocations are not allowed.
 */
typedef struct arc_slist * arc_slist_t;
/**
 * @typedef arc_slist_node_t
 * @brief List node definition
 *
 * The list node is used as an iterator to access internal elements of the list.
 */
typedef struct arc_slist_node * arc_slist_node_t;

/**
 * @brief Creates a new list
 *
 * Creates a new list in the heap, the memory has to be destroyed y the user and 
 * the data size provided has to coincide with the element type size to be used 
 * in the container. 
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
 */
int arc_slist_size(arc_slist_t list);
/**
 * @brief Returns whether the list is empty or not
 *
 * @param[in] list List to perform the operation on
 */
int arc_slist_empty(arc_slist_t list);
/**
 * @brief CLears the contents of the list
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
 * @brief Removes the first element from the stack
 *
 * @param[in] list List to perform the operation on
 */
void arc_slist_pop_front(arc_slist_t list);
/**
 * @brief Adds a new element to the front of the list
 *
 * @param[in] list List to perform the operation on
 */
int arc_slist_push_front(arc_slist_t list, void * data);
/**
 * @brief Returns a node to the element before the beginning of the list
 *
 * @param[in] list List to perform the operation on
 */
arc_slist_node_t arc_slist_before_begin(arc_slist_t list);
/**
 * @brief Returns a node to the initial element of the list
 *
 * @param[in] list List to perform the operation on
 */
arc_slist_node_t arc_slist_begin(arc_slist_t list);
/**
 * @brief Returns a node to the element after the end of the list
 *
 * @param[in] list List to perform the operation on
 */
arc_slist_node_t arc_slist_after_end(arc_slist_t list);
/**
 * @brief Adds an element after the node
 *
 * @param[in] list List to perform the operation on
 */
int arc_slist_insert_after(arc_slist_node_t it, void * data);
/**
 * @brief Removes the node from the list
 *
 * @param[in] list List to perform the operation on
 */
void arc_slist_erase_after(arc_slist_node_t it);
/**
 * @brief Returns whether the node is valid or not (accessible)
 *
 * @param[in] list List to perform the operation on
 * @retval 0 If the node is invalid
 * @retval 1 If the node is valid
 */
int arc_slist_node_valid(arc_slist_node_t it);
/**
 * @brief Returns the data associated to the node
 *
 * @param[in] list List to perform the operation on
 * @return Data pointer of the node
 */
void * arc_slist_node_data(arc_slist_node_t it);
/**
 * @brief Gets the next node in the list
 *
 * @param[in] list List to perform the operation on
 */
arc_slist_node_t arc_slist_node_next(arc_slist_node_t it);

#endif