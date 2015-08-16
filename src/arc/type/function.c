/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

/******************************************************************************/

int arc_cmp_char(void * a, void * b)
{
    return *((char *)a) < *((char *)b) ? -1 : *((char *)a) > *((char *)b);
}

/******************************************************************************/

int arc_cmp_schar(void * a, void * b)
{
    return *((signed char *)a) < *((signed char *)b) ?
                -1 : *((signed char *)a) > *((signed char *)b);
}

/******************************************************************************/

int arc_cmp_uchar(void * a, void * b)
{
    return *((unsigned char *)a) < *((unsigned char *)b) ?
                -1 : *((unsigned char *)a) > *((unsigned char *)b);
}

/******************************************************************************/

int arc_cmp_int(void * a, void * b)
{
    return *((int *)a) < *((int *)b) ? -1 : *((int *)a) > *((int *)b);
}

/******************************************************************************/

int arc_cmp_uint(void * a, void * b)
{
    return *((unsigned *)a) < *((unsigned *)b) ?
                -1 : *((unsigned *)a) > *((unsigned *)b);
}

/******************************************************************************/

int arc_cmp_long(void * a, void * b)
{
    return *((long *)a) < *((long *)b) ? -1 : *((long *)a) > *((long *)b);
}

/******************************************************************************/

int arc_cmp_ulong(void * a, void * b)
{
    return *((unsigned long *)a) < *((unsigned long *)b) ?
                -1 : *((unsigned long *)a) > *((unsigned long *)b);
}

/******************************************************************************/

int arc_cmp_float(void * a, void * b)
{
    return *((float *)a) < *((float *)b) ? -1 : *((float *)a) > *((float *)b);
}

/******************************************************************************/

int arc_cmp_double(void * a, void * b)
{
    return *((double *)a) < *((double *)b) ?
                -1 : *((double *)a) > *((double *)b);
}

/******************************************************************************/
