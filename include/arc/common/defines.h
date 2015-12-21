/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup Defines
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 * @ingroup Common
 *
 * @brief General defines
 */

#ifndef ARC_DEFINES_H_
#define ARC_DEFINES_H_

#if defined(__STDC__)
# define ARC_C89
# if defined(__STDC_VERSION__)
#  define ARC_C90
#  if (__STDC_VERSION__ >= 199409L)
#   define ARC_C94
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define ARC_C99
#  endif
# endif
#endif

#ifdef __cplusplus
extern "C"{
#endif

#ifdef ARC_C99
# include <stdint.h>
#else
/** @brief Maximum size of size_t type */
# define SIZE_MAX ULONG_MAX
#endif

/** @brief Return value to indicate success in the operation */
#define ARC_SUCCESS        0
/** @brief Return value to indicate a generic error */
#define ARC_ERROR         -1
/** @brief Return value to indicate an out of memory error */
#define ARC_OUT_OF_MEMORY -2
/** @brief Return value to indicate an element is duplicated in a structure */
#define ARC_DUPLICATE     -3

/** @brief Returns the offset of the field in the struct */
#define ARC_OFFSETOF(type, field) ((size_t) &(((type *) 0)->field))

/** @brief Used to mark variables as unused */
#define ARC_UNUSED(x) (void)(x)

#ifndef NDEBUG
#define ARC_DEBUG(fmt) printf(fmt);fflush(stdout);
#define ARC_DEBUG1(fmt,param1) printf(fmt,param1);fflush(stdout);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ARC_DEFINES_H_ */

/** @} */
