/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup BSTree
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date December, 2014
 * @ingroup Container
 *
 * @brief Binary Search Tree
 *
 * A binary search tree is a data structure in which each node contains a right
 * and a left link. The right link points to a node containing a value bigger
 * than the current nodes value, similarly the left link points to a node
 * containing a value smaller than the current nodes value, hence the data
 * structure is inherently ordered.
 *
 * For more information and examples check the documentation (\ref page_bstree).
 *
 * @see http://en.wikipedia.org/wiki/Binary_search_tree
 */

#ifndef ARC_BSTREE_H_
#define ARC_BSTREE_H_

#include <stdlib.h>
#include <arc/type/function.h>
#include <arc/container/iterator.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_bstree_t
 * @brief Binary search tree definition
 *
 */
typedef struct arc_tree * arc_bstree_t;

/**
 * @brief Creates a new bstree
 *
 * @param[in] data_size Size of the data element
 * @param[in] cmp_fn Comparison function (-1, 0, 1)
 * @return New empty bstree
 * @retval NULL if memory cannot be allocated
 */
arc_bstree_t arc_bstree_create(size_t data_size, arc_cmp_fn_t cmp_fn);
/**
 * @brief Destroys the memory associated to a bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_destroy(arc_bstree_t bstree);
/**
 * @brief Inserts an element into the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data Data element to be inserted
 * @retval ARC_SUCCESS If the element was inserted successfully
 * @retval ARC_DUPLICATE If the element is already in the bstree
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 */
int arc_bstree_insert(arc_bstree_t bstree, void * data);
/**
 * @brief Finds an element in the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data Data element to be found
 * @retval 0 If the element was not found
 * @retval 1 If the element was found
 */
int arc_bstree_find(arc_bstree_t bstree, void * data);
/**
 * @brief Returns whether the bstree is empty or not
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @retval 0 If the bstree is not empty
 * @retval 1 If the bstree is empty
 */
int arc_bstree_empty(arc_bstree_t bstree);
/**
 * @brief Returns the size of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @return Size of the bstree
 */
size_t arc_bstree_size(arc_bstree_t bstree);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_clear(arc_bstree_t bstree);
/**
 * @brief Creates an optimal BST using the Day–Stout–Warren algorithm
 *
 * @see https://en.wikipedia.org/wiki/Day%E2%80%93Stout%E2%80%93Warren_algorithm
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_rebalance(arc_bstree_t bstree);
/**
 * @brief Removes an element from the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @param[in] data Data element to be removed
 */
void arc_bstree_remove(arc_bstree_t bstree, void * data);
/**
 * @brief Sets an iterator to the element before the beginning of the bstree
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_bstree_before_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the initial element of the bstree
 *
 * @param[in] it Iterator
 */
void arc_bstree_begin(arc_iterator_t it);
/**
 * @brief Sets an iterator to the last element of the bstree
 *
 * @param[in] it Iterator
 */
void arc_bstree_end(arc_iterator_t it);
/**
 * @brief Sets an iterator to the element after the end of the bstree
 *
 * @warning The data pointer of this iterator must not be requested, the
 *          iterator cannot be dereferenced as there is no memory allocated
 *          for data.
 *
 * @param[in] it Iterator
 */
void arc_bstree_after_end(arc_iterator_t it);
/**
 * @brief Returns the data associated to the Iterator
 *
 * @param[in] it Iterator
 * @return Data pointer of the node
 */
void * arc_bstree_data(arc_iterator_t it);
/**
 * @brief Sets an iterator to the specified element of the bstree
 *
 * @param[in] it Iterator
 * @param[in] data Element index
 * @retval 0 If the bstree is not empty
 * @retval 1 If the bstree is empty
 */
int arc_bstree_position(arc_iterator_t it, void * data);
/**
 * @brief Removes the iterator position from the bstree
 *
 * @param[in] it Iterator
 */
void arc_bstree_erase(arc_iterator_t it);
/**
 * @brief Sets the iterator to the next node in the bstree
 *
 * @param[in] it Iterator
 * @retval 0 If the element after the end of the bstree has been reached
 * @retval 1 If the current element is in the bstree
 */
int arc_bstree_next(arc_iterator_t it);
/**
 * @brief Sets the iterator to the previous node in the bstree
 *
 * @param[in] it Iterator
 * @retval 0 If the element before the beginning of the bstree has been reached
 * @retval 1 If the current element is in the bstree
 */
int arc_bstree_previous(arc_iterator_t it);

#ifdef __cplusplus
}
#endif

#endif /* ARC_BSTREE_H_ */

/** @} */
