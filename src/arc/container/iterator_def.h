/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

/**
 * @struct arc_iterator
 * @brief Iterator definition
 */
struct arc_iterator
{
    void * container;
    void * node_ptr;
    unsigned long node_num;
    unsigned long node_idx;
};
