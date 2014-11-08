/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file integer.h
 * @author Anil M. Mahtani Mirchandani
 * @date November, 2014
 */

#include <limits.h>

#ifdef ARC_C99
    #include <stdint.h>
#else
    #define SIZE_MAX ULONG_MAX

    typedef signed char    int8_t;
    typedef signed short   int16_t;
    typedef signed int     int32_t;
    typedef signed long    int64_t;

    typedef unsigned char  uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int   uint32_t;
    typedef unsigned long  uint64_t;

#endif