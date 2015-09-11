/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file function.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Function type definitions
 */

#ifndef ARC_FUNCTION_H_
#define ARC_FUNCTION_H_

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_compare_fn_t
 * @brief Comparison function
 */
typedef int (*arc_cmp_fn_t)(void *, void *);

int arc_cmp_char(void * a, void * b);
int arc_cmp_schar(void * a, void * b);
int arc_cmp_uchar(void * a, void * b);
int arc_cmp_int(void * a, void * b);
int arc_cmp_uint(void * a, void * b);
int arc_cmp_long(void * a, void * b);
int arc_cmp_ulong(void * a, void * b);
int arc_cmp_float(void * a, void * b);
int arc_cmp_double(void * a, void * b);


/**
 * @typedef arc_hash_fn_t
 * @brief Hash function
 */
typedef unsigned long (*arc_hash_fn_t)(void *, size_t);

#ifdef __cplusplus
}
#endif

#endif
