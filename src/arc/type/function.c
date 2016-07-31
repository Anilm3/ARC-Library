/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

/******************************************************************************/

int arc_cmp_char(const void * a, const void * b)
{
    return *((const char *)a) < *((const char *)b) ? 
                -1 : *((const char *)a) > *((const char *)b);
}

/******************************************************************************/

int arc_cmp_schar(const void * a, const void * b)
{
    return *((const signed char *)a) < *((const signed char *)b) ?
                -1 : *((const signed char *)a) > *((const signed char *)b);
}

/******************************************************************************/

int arc_cmp_uchar(const void * a, const void * b)
{
    return *((const unsigned char *)a) < *((const unsigned char *)b) ?
                -1 : *((const unsigned char *)a) > *((const unsigned char *)b);
}

/******************************************************************************/

int arc_cmp_int(const void * a, const void * b)
{
    return *((const int *)a) < *((const int *)b) ?
                -1 : *((const int *)a) > *((const int *)b);
}

/******************************************************************************/

int arc_cmp_uint(const void * a, const void * b)
{
    return *((const unsigned *)a) < *((const unsigned *)b) ?
                -1 : *((const unsigned *)a) > *((const unsigned *)b);
}

/******************************************************************************/

int arc_cmp_long(const void * a, const void * b)
{
    return *((const long *)a) < *((const long *)b) ?
                -1 : *((const long *)a) > *((const long *)b);
}

/******************************************************************************/

int arc_cmp_ulong(const void * a, const void * b)
{
    return *((const unsigned long *)a) < *((const unsigned long *)b) ?
                -1 : *((const unsigned long *)a) > *((const unsigned long *)b);
}

/******************************************************************************/

int arc_cmp_float(const void * a, const void * b)
{
    return *((const float *)a) < *((const float *)b) ?
                -1 : *((const float *)a) > *((const float *)b);
}

/******************************************************************************/

int arc_cmp_double(const void * a, const void * b)
{
    return *((const double *)a) < *((const double *)b) ?
                -1 : *((const double *)a) > *((const double *)b);
}

/******************************************************************************/
