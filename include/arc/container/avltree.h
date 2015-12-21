/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup AVLTree
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date December, 2015
 * @ingroup Container
 *
 * @brief Adelson velsky Landis (AVL) Tree
 *
 * A binary search tree is a data structure in which each node contains a right
 * and a left link. The right link points to a node containing a value bigger
 * than the current nodes value, similarly the left link points to a node
 * containing a value smaller than the current nodes value, hence the data
 * structure is inherently ordered.
 *
 * For more information and examples check the documentation (\ref page_avltree).
 *
 * @see http://en.wikipedia.org/wiki/Binary_search_tree
 */

#ifndef ARC_AVLTREE_H_
#define ARC_AVLTREE_H_

#include <stdlib.h>
#include <arc/type/function.h>
#include <arc/container/iterator.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_avltree_t
 * @brief Binary search tree definition
 *
 */
typedef struct arc_avltree * arc_avltree_t;

/**
 * @brief Creates a new avltree
 *
 * @param[in] data_size Size of the data element
 * @param[in] cmp_fn Comparison function (-1, 0, 1)
 * @return New empty avltree
 * @retval NULL if memory cannot be allocated
 */
arc_avltree_t arc_avltree_create(size_t data_size, arc_cmp_fn_t cmp_fn);
/**
 * @brief Destroys the memory associated to a avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 */
void arc_avltree_destroy(arc_avltree_t avltree);
/**
 * @brief Inserts an element into the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @param[in] data Data element to be inserted
 * @retval ARC_SUCCESS If the element was inserted successfully
 * @retval ARC_DUPLICATE If the element is already in the avltree
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 */
int arc_avltree_insert(arc_avltree_t avltree, void * data);
/**
 * @brief Finds an element in the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @param[in] data Data element to be found
 * @retval 0 If the element was not found
 * @retval 1 If the element was found
 */
int arc_avltree_find(arc_avltree_t avltree, void * data);
/**
 * @brief Returns whether the avltree is empty or not
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @retval 0 If the avltree is not empty
 * @retval 1 If the avltree is empty
 */
int arc_avltree_empty(arc_avltree_t avltree);
/**
 * @brief Returns the size of the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @return Size of the avltree
 */
size_t arc_avltree_size(arc_avltree_t avltree);
/**
 * @brief Clears the contents of the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 */
void arc_avltree_clear(arc_avltree_t avltree);
/**
 * @brief Removes an element from the avltree
 *
 * @param[in] avltree Binary search tree to perform the operation on
 * @param[in] data Data element to be removed
 */
void arc_avltree_remove(arc_avltree_t avltree, void * data);
/**
 * @brief Sets an iterator to the element before the beginning of the avltree
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_avltree_before_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the initial element of the avltree
 *
 * @param[in] it Iterator
 */
void arc_avltree_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the last element of the avltree
 *
 * @param[in] it Iterator
 */
void arc_avltree_end(arc_iterator_t it);
/**
 * @brief Sets an iterator to the element after the end of the avltree
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_avltree_after_end(arc_iterator_t it);
/**
 * @brief Returns the data associated to the Iterator
 *
 * @param[in] it Iterator
 * @return Data pointer of the node
 */
void * arc_avltree_data(arc_iterator_t it);
/**
 * @brief Sets an iterator to the specified element of the avltree
 *
 * @param[in] it Iterator
 * @param[in] data Element index
 * @retval 0 If the avltree is not empty
 * @retval 1 If the avltree is empty
 */
int arc_avltree_position(arc_iterator_t it, void * data);
/**
 * @brief Removes the iterator position from the avltree
 *
 * @param[in] it Iterator
 */
void arc_avltree_erase(arc_iterator_t it);
/**
 * @brief Sets the iterator to the next node in the avltree
 *
 * @param[in] it Iterator
 * @retval 0 If the element after the end of the avltree has been reached
 * @retval 1 If the current element is in the avltree
 */
int arc_avltree_next(arc_iterator_t it);
/**
 * @brief Sets the iterator to the previous node in the avltree
 *
 * @param[in] it Iterator
 * @retval 0 If the element before the beginning of the avltree has been reached
 * @retval 1 If the current element is in the avltree
 */
int arc_avltree_previous(arc_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif /* ARC_AVLTREE_H_ */

/** @} */
