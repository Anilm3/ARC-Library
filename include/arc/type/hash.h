/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup Function
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date September, 2015
 * @ingroup Type
 *
 * @brief Hash function and type definition
 */
#ifndef ARC_HASH_H_
#define ARC_HASH_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
/**
 * @typedef arc_hkey_t
 * @brief Hash key type definition
 */
typedef unsigned long arc_hkey_t;
/**
 * @typedef arc_hash_fn_t
 * @brief Hash function type definition
 */
typedef arc_hkey_t (*arc_hash_fn_t)(const void *, size_t);

/**
 * @brief Computes a hash value for a block of memory
 *
 * The implementation follows the Pearson Hashing algorithm to create a uniform
 * distribution from any non-uniform (or uniform) distribution of keys.
 * @see https://en.wikipedia.org/wiki/Pearson_hashing
 *
 * @param[in] data Data block from which to compute the hash value
 * @param[in] data_size Size of the data element
 * @return Hash value for the block of data
 */
arc_hkey_t arc_hash_pearson(const void *data, size_t data_size);
arc_hkey_t arc_hash_djb2(const void *data, size_t data_size);

#ifdef __cplusplus
}
#endif

#endif /* ARC_FUNCTION_H_ */

/** @} */