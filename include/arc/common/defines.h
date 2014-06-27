/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @author Anil M. Mahtani Mirchandani
 * @file defines.h
 * @date June, 2014
 *
 * @brief General defines
 */

#ifndef ARC_DEFINES_H_
#define ARC_DEFINES_H_

#ifdef __cplusplus
extern "C"{
#endif 

/** @brief Return value to indicate success in the operation */
#define ARC_SUCCESS        0
/** @brief Return value to indicate a generic error */
#define ARC_ERROR         -1
/** @brief Return value to indicate an out of memory error */
#define ARC_OUT_OF_MEMORY -2

/** @brief Returns the offset of the field in the struct */
#define ARC_OFFSETOF(type, field) ((size_t) &(((type *) 0)->field))

#ifdef __cplusplus
}
#endif

#endif