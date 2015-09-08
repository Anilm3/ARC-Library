/*******************************************************************************
* Copyright (C) 2015 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file htable.c
 * @author Anil M. Mahtani Mirchandani
 * @date August, 2015
 *
 * @brief HTable
 *
 * @see https://en.wikipedia.org/wiki/Hash_table
 */
#ifndef ARC_HTABLE_DEF_H_
#define ARC_HTABLE_DEF_H_

#include <stdlib.h>
#include <arc/type/function.h>
#include <arc/container/slist.h>

#define NUM_BUCKETS 32


struct arc_htable
{
    size_t data_size;
    size_t key_size;
    size_t size;
    arc_hash_fn_t hash_fn;
    arc_slist_t buckets[NUM_BUCKETS];
};

struct arc_htable_node
{
    void *key;
    void *data;
};

#endif
