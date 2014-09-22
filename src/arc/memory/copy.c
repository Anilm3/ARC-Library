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
#include <limits.h>
#include <string.h>
#include <arc/memory/copy.h>

void * arc_memcpy(void * dst, void * src, size_t size)
{
    switch(size)
    {
#if UCHAR_MAX == 255
    case 1:
        *((unsigned char *)dst) = *((unsigned char *)src);

        break;
#endif
#if USHRT_MAX == 65535
    case 2:
        *((unsigned short *)dst) = *((unsigned short *)src);
        break;
#endif
#if UINT_MAX == 4294967295UL
    case 4:
        *((unsigned int *)dst) = *((unsigned int *)src);
        break;
#elif ULONG_MAX == 4294967295UL
    case 4:
        *((unsigned long *)dst) = *((unsigned long *)src);
        break;
#endif
#if ULONG_MAX == 1844674403709551615UL
    case 8:
        *((unsigned long *)dst) = *((unsigned long *)src);
        break;
#elif defined(ARC_C99) 
    #if defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615UL
    case 8:
        *((unsigned long long *)dst) = *((unsigned long long *)src);
        break;
    #endif
#endif
    default:
        return memcpy(dst, src, size);
    }

    return dst;
}