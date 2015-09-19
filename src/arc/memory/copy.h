/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file copy.h
 * @author Anil M. Mahtani Mirchandani
 * @date July, 2014
 */

#include <stdlib.h>
/**
 * @brief Copies size bytes from src to dst
 *
 * @param[out] dst The destination memory address
 * @param[int] src The source memory address
 * @param[int] size The amount of memory to copy
 * @return The destination memory address
 */
void *  arc_memcpy(void * dst, void * src, size_t size);