/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file iterator.h
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
 
#ifndef ARC_ITERATOR_H_
#define ARC_ITERATOR_H_

#include <stdlib.h> 

/**
 * @typedef arc_iterator_t
 * @brief List definition
 *
 * The list is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_iterator * arc_iterator_t;
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
arc_iterator_t arc_iterator_create(void * container);
/**
 * @brief Destroys the memory associated to a list 
 *
 * @param[in] list List to perform the operation on
 */
void arc_iterator_destroy(arc_iterator_t list);

#endif