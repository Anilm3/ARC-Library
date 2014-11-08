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
#include <limits.h>
#include <arc/memory/memory.h>
#include <arc/type/integer.h>
#include <errno.h>

/******************************************************************************/
 
void * arc_malloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

/******************************************************************************/

void * arc_realloc(void *ptr, size_t nmemb, size_t size)
{
    void * newptr;

    if (nmemb && size && (SIZE_MAX / nmemb) < size)
    {
        errno = ENOMEM;
        return NULL;
    }

    newptr = realloc(ptr, nmemb * size);
    if (newptr == NULL)
    {
        return NULL;
    }

    return newptr;
}

/******************************************************************************/