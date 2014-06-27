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
 * @brief Generic iterator
 *
 * A generic iterator is a common type of iterator that can be used for any
 * data structure. It is not allowed to use the same iterator for other data
 * structures other than the one specified for the iterator
 *
 * @see http://en.wikipedia.org/wiki/Iterator
 */
 
#ifndef ARC_ITERATOR_H_
#define ARC_ITERATOR_H_

#include <stdlib.h> 

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @typedef arc_iterator_t
 * @brief List definition
 *
 * The iterator is defined as a pointer to be used with the creation and 
 * destruction functions, direct stack allocations are not allowed.
 */
typedef struct arc_iterator * arc_iterator_t;
/**
 * @brief Creates a new iterator
 *
 * The memory is allocated in the heap and has to be destroyed by the user. 
 *
 * @param[in] container Container to iterate through
 * @return New iterator for the specified container
 * @retval NULL if memory cannot be allocated
 */
arc_iterator_t arc_iterator_create(void * container);
/**
 * @brief Destroys the memory associated to a iterator 
 *
 * @param[in] it Iterator to delete
 */
void arc_iterator_destroy(arc_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif