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
#include <arc/container/htable.h>
#include <arc/container/avltree_def.h>

struct arc_htable
{
    size_t num_buckets;
    size_t data_size;
    size_t size;
    arc_cmp_fn_t cmp_fn;
    arc_hash_fn_t hash_fn;
    struct arc_tree *buckets;
};

struct arc_htable_node
{
    void *key;
    void *data;
};

int arc_htable_initialize(struct arc_htable *htable,
                          size_t num_buckets,
                          size_t data_size,
                          arc_cmp_fn_t cmp_fn,
                          arc_hash_fn_t hash_fn);

void arc_htable_finalize(struct arc_htable *htable);

#endif
