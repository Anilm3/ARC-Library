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

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <arc/common/defines.h>
#include <arc/type/function.h>
#include <arc/container/htable.h>
#include <arc/container/avltree.h>
#include <arc/container/htable_def.h>
#include <arc/container/iterator_def.h>

/******************************************************************************/

/*size_t arc_htable_max(struct arc_htable * htable)*/
/*{*/
    /*size_t i, max_value = 0;*/

    /*for (i = 0; i < htable->num_buckets; i++)*/
    /*{*/
        /*if (arc_slist_size(&htable->buckets[i]) > max_value)*/
        /*{*/
            /*max_value = arc_slist_size(&htable->buckets[i]);*/
        /*}*/
    /*}*/

    /*return max_value;*/
/*}*/

/******************************************************************************/

/*double arc_htable_variance(struct arc_htable * htable)*/
/*{*/
    /*size_t i;*/
    /*double variance = 0;*/
    /*double mean = (double)htable->size / (double) htable->num_buckets;*/

    /*for (i = 0; i < htable->num_buckets; i++)*/
    /*{*/
        /*variance += pow((double)arc_slist_size(&htable->buckets[i]) - mean, 2);*/
    /*}*/

    /*variance /= (double)htable->num_buckets;*/

    /*return variance;*/
/*}*/

/******************************************************************************/

int arc_htable_initialize(struct arc_htable *htable,
                          size_t num_buckets,
                          size_t data_size,
                          arc_cmp_fn_t cmp_fn,
                          arc_hash_fn_t hash_fn)
{
    size_t i;

    htable->buckets = malloc(sizeof(struct arc_tree) * num_buckets);

    if (htable->buckets == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    htable->num_buckets = num_buckets;
    htable->data_size = data_size;
    htable->size = 0;
    htable->cmp_fn = cmp_fn;
    htable->hash_fn = hash_fn;

    for (i = 0; i < num_buckets; i++)
    {
        int retval = arc_avltree_initialize(&htable->buckets[i], data_size, cmp_fn);

        if (retval != ARC_SUCCESS)
        {
            size_t j;

            for (j = 0; j < i; j++)
            {
                arc_avltree_finalize(&htable->buckets[i]);
            }

            free(htable->buckets);

            return retval;
        }
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_htable_finalize(struct arc_htable *htable)
{
    arc_htable_clear(htable);
    free(htable->buckets);
}

/******************************************************************************/

struct arc_htable * arc_htable_create(size_t num_buckets,
                                      size_t data_size,
                                      arc_cmp_fn_t cmp_fn,
                                      arc_hash_fn_t hash_fn)
{
    struct arc_htable * htable = malloc(sizeof(struct arc_htable));

    if (htable == NULL)
    {
        return htable;
    }

    if (arc_htable_initialize(htable, num_buckets, 
                              data_size, cmp_fn, hash_fn) != ARC_SUCCESS)
    {
        free(htable);
        return NULL;
    }

    return htable;
}

/******************************************************************************/

void arc_htable_destroy(struct arc_htable * htable)
{
    arc_htable_finalize(htable);
    free(htable);
}

/******************************************************************************/

int arc_htable_insert(struct arc_htable *htable, void *data)
{
    arc_hkey_t hvalue;
    hvalue = htable->hash_fn(data, htable->data_size) % htable->num_buckets;

    return arc_avltree_insert(&htable->buckets[hvalue], data);
}

/******************************************************************************/

void * arc_htable_retrieve(struct arc_htable * htable, void *data)
{
    arc_hkey_t hvalue;

    hvalue = htable->hash_fn(data, htable->data_size) % htable->num_buckets;

    return arc_avltree_retrieve(&htable->buckets[hvalue], data);
}

/******************************************************************************/

int arc_htable_empty(struct arc_htable * htable)
{
    return (htable->size == 0);
}

/******************************************************************************/

size_t arc_htable_size(struct arc_htable * htable)
{
    return htable->size;
}

/******************************************************************************/

void arc_htable_clear(struct arc_htable * htable)
{
    size_t i;

    for (i = 0; i < htable->num_buckets; i++)
    {
        arc_avltree_clear(&htable->buckets[i]);
    }
    htable->size = 0;
}

/******************************************************************************/

void arc_htable_remove(struct arc_htable * htable, void *data)
{
    arc_hkey_t hvalue;

    hvalue = htable->hash_fn(data, htable->data_size) % htable->num_buckets;

    arc_avltree_remove(&htable->buckets[hvalue], data);
}

/******************************************************************************/

/*int arc_htable_rehash(struct arc_htable * htable, size_t num_buckets)*/
/*{*/
    /*size_t i;*/
    /*struct arc_slist *buckets = malloc(sizeof(struct arc_slist) * num_buckets);*/

    /*if (buckets == NULL)*/
    /*{*/
        /*return ARC_OUT_OF_MEMORY;*/
    /*}*/

    /*for (i = 0; i < num_buckets; i++)*/
    /*{*/
        /*arc_slist_initialize(&buckets[i], sizeof(struct arc_htable_node));*/
    /*}*/

    /*for (i = 0; i < htable->num_buckets; i++)*/
    /*{*/
        /*arc_hkey_t hvalue ;*/

        /*if (arc_slist_size(&htable->buckets[i]) > 0)*/
        /*{*/
            /*struct arc_iterator it;*/
            /*arc_iterator_initialize(&it, &htable->buckets[i]);*/

            /*arc_slist_before_begin(&it);*/

            /*while(arc_slist_next(&it))*/
            /*{*/
                /*void *data = arc_slist_data(&it);*/

                /*hvalue = htable->hash_fn(data, htable->data_size) %*/
                         /*num_buckets;*/
                /*arc_slist_insert_order(&buckets[hvalue], htable->cmp_fn, data);*/
/*[>                arc_slist_push_front(&buckets[hvalue], node); <]*/
            /*}*/

            /*arc_iterator_finalize(&it);*/
        /*}*/

        /*arc_slist_finalize(&htable->buckets[i]);*/
    /*}*/

    /*free(htable->buckets);*/
    /*htable->buckets = buckets;*/
    /*htable->num_buckets = num_buckets;*/

    /*return ARC_SUCCESS;*/
/*}*/

/******************************************************************************/
