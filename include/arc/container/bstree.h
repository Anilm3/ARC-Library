/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file bstree.h
 * @author Anil M. Mahtani Mirchandani
 * @date December, 2014
 *
 * @brief
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
typedef struct arc_bstree * arc_bstree_t;

/**
 * @brief Creates a new bstree
 *
 * @param[in] data_size Size of the data element
 * @param[in] cmp_fn Comparison function (<)
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
 * @brief Returns whether the bstree is empty or not
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @retval 0 If the bstree is not empty
 * @retval 1 If the bstree is empty
 */
int arc_bstree_insert(arc_bstree_t bstree, void * data);
/**
 * @brief Returns whether the bstree is empty or not
 *
 * @param[in] bstree Binary search tree to perform the operation on
 * @retval 0 If the bstree is not empty
 * @retval 1 If the bstree is empty
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
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_remove(arc_bstree_t bstree, void * data);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_before_begin(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_begin(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_end(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_after_end(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
int arc_bstree_next(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
int arc_bstree_previous(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void * arc_bstree_data(arc_iterator_t it);
/**
 * @brief Clears the contents of the bstree
 *
 * @param[in] bstree Binary search tree to perform the operation on
 */
void arc_bstree_erase(struct arc_iterator * it);
#ifdef __cplusplus
}
#endif

#endif /* ARC_BSTREE_H_ */