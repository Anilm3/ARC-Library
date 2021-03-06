/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
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
 * @date June, 2014
 * @ingroup Type
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
typedef int (*arc_cmp_fn_t)(const void *, const void *);

int arc_cmp_char(const void * a, const void * b);
int arc_cmp_schar(const void * a, const void * b);
int arc_cmp_uchar(const void * a, const void * b);
int arc_cmp_int(const void * a, const void * b);
int arc_cmp_uint(const void * a, const void * b);
int arc_cmp_long(const void * a, const void * b);
int arc_cmp_ulong(const void * a, const void * b);
int arc_cmp_float(const void * a, const void * b);
int arc_cmp_double(const void * a, const void * b);

#ifdef __cplusplus
}
#endif

#endif /* ARC_FUNCTION_H_ */

/** @} */
