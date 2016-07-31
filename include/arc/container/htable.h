/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup HTable
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date August, 2015
 * @ingroup Container
 *
 * @brief Hash Table
 *
 * Implementation of a static hash table.
 *
 * For more information and examples check the documentation
 * (\ref page_dhtable).
 *
 * @see https://en.wikipedia.org/wiki/Hash_table
 */

#ifndef ARC_HTABLE_H_
#define ARC_HTABLE_H_

#include <stdlib.h>
#include <arc/type/hash.h>
#include <arc/type/function.h>
#include <arc/container/iterator.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_htable_t
 * @brief Hash table definition
 *
 */
typedef struct arc_htable * arc_htable_t;

/**
 * @brief Creates a new htable
 *
 * @param[in] num_buckets Number of buckets in the hash table
 * @param[in] key_size Size of the key
 * @param[in] data_size Size of the data element
 * @param[in] hash_fn Hash function for the key type
 * @return New empty htable
 * @retval NULL if memory cannot be allocated
 */
arc_htable_t arc_htable_create(size_t num_buckets,
                               size_t data_size,
                               arc_cmp_fn_t cmp_fn,
                               arc_hash_fn_t hash_fn);
/**
 * @brief Destroys the memory associated to a htable
 *
 * @param[in] htable Hash table to perform the operation on
 */
void arc_htable_destroy(arc_htable_t htable);

/**
 * @brief Inserts an element into the htable
 *
 * @param[in] htable Hash table to perform the operation on
 * @param[in] key Key associated to the data to be inserted
 * @param[in] data Data element to be inserted
 * @retval ARC_SUCCESS If the element was inserted successfully
 * @retval ARC_DUPLICATE If the element is already in the htable
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 */
int arc_htable_insert(arc_htable_t htable, void *data);
/**
 * @brief Retrieves the data associated to a key in the hash table
 *
 * @param[in] htable Hash table to perform the operation on
 * @param[in] key Key of the data element to be found
 * @return Data element associated to the key
 * @retval NULL If the element was not found
 */
void *arc_htable_retrieve(arc_htable_t htable, void *data);
/**
 * @brief Returns whether the htable is empty or not
 *
 * @param[in] htable Hash table to perform the operation on
 * @retval 0 If the htable is not empty
 * @retval 1 If the htable is empty
 */
int arc_htable_empty(arc_htable_t htable);
/**
 * @brief Returns the size of the htable
 *
 * @param[in] htable Hash table to perform the operation on
 * @return Size of the htable
 */
size_t arc_htable_size(arc_htable_t htable);
/**
 * @brief Clears the contents of the htable
 *
 * @param[in] htable Hash table to perform the operation on
 */
void arc_htable_clear(arc_htable_t htable);
/**
 * @brief Removes an element from the htable
 *
 * @param[in] htable Hash table to perform the operation on
 * @param[in] key Key of the data element to be removed
 */
void arc_htable_remove(arc_htable_t htable, void *data);
/**
 * @brief Reestructures the table to contain the specified number of buckets
 *
 * @param[in] htable Hash table to perform the operation on
 * @param[in] num_buckets Number of buckets in the hash table
 * @retval ARC_SUCCESS If the rehashing was completed successfully
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 */
int arc_htable_rehash(arc_htable_t htable, size_t num_buckets);

#ifdef __cplusplus
}
#endif

#endif /* ARC_HTABLE_H_ */

/** @} */
