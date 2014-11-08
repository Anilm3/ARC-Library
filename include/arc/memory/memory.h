/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file memory.h
 * @author Anil M. Mahtani Mirchandani
 * @date November, 2014
 */

#include <stdlib.h>
/**
 * @brief Allocates a memory block of size nmemb*size
 *
 * @param[in] nmemb Number of elements to allocate
 * @param[in] size Size of each element
 * @return Pointer to the allocated memory block
 */
void * arc_malloc(size_t nmemb, size_t size);
/**
 * @brief Resizes the given memory block
 *
 * @param[in] ptr Memory block to resize
 * @param[in] nmemb New number of elements the block should contain
 * @param[in] size Size of each element
 * @return Data pointer to the new memory block
 */
void * arc_realloc(void *ptr, size_t nmemb, size_t size);