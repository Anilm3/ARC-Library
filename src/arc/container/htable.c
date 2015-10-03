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
#include <arc/container/slist.h>
#include <arc/container/htable_def.h>
#include <arc/container/iterator_def.h>
/******************************************************************************/

size_t arc_htable_max(struct arc_htable * htable)
{
    size_t i, max_value = 0;

    for (i = 0; i < htable->num_buckets; i++)
    {
        if (arc_slist_size(htable->buckets[i]) > max_value)
        {
            max_value = arc_slist_size(htable->buckets[i]);
        }
    }

    return max_value;
}

/******************************************************************************/

double arc_htable_variance(struct arc_htable * htable)
{
    size_t i;
    double variance = 0;
    double mean = (double)htable->size / (double) htable->num_buckets;

    for (i = 0; i < htable->num_buckets; i++)
    {
        variance += pow((double)arc_slist_size(htable->buckets[i]) - mean, 2);
    }

    variance /= (double)htable->num_buckets;

    return variance;
}

/******************************************************************************/

struct arc_htable * arc_htable_create(size_t num_buckets,
                                      size_t key_size,
                                      size_t data_size,
                                      arc_hash_fn_t hash_fn)
{
    size_t i;
    struct arc_htable * htable = malloc(sizeof(struct arc_htable));

    htable->buckets = malloc(sizeof(arc_slist_t) * num_buckets);
    htable->num_buckets = num_buckets;
    htable->key_size = key_size;
    htable->data_size = data_size;
    htable->size = 0;
    htable->hash_fn = hash_fn;

    for (i = 0; i < num_buckets; i++)
    {
        htable->buckets[i] = arc_slist_create(sizeof(struct arc_htable_node));
    }

    return htable;
}

/******************************************************************************/

void arc_htable_destroy(struct arc_htable * htable)
{
    arc_htable_clear(htable);
    free(htable->buckets);
    free(htable);
}

/******************************************************************************/

int arc_htable_insert(struct arc_htable * htable, void * key, void * data)
{
    arc_hkey_t hvalue;
    arc_slist_t list;
    struct arc_iterator it;
    struct arc_htable_node node;
    int duplicate = 0;

    hvalue = htable->hash_fn(key, htable->key_size) % htable->num_buckets;
    list = htable->buckets[hvalue];

    node.key = malloc(htable->key_size);

    if (node.key == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node.data = malloc(htable->data_size);

    if (node.data == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    memcpy(node.key, key, htable->key_size);
    memcpy(node.data, data, htable->data_size);

    /* TODO: Optimize by creating stack iterators */
    if (arc_slist_size(list) > 0)
    {
        arc_iterator_initialize(&it, list);

        arc_slist_before_begin(&it);

        while(arc_slist_next(&it))
        {
            struct arc_htable_node * list_node = arc_slist_data(&it);
            if(memcmp(list_node->key, key, htable->key_size) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        arc_iterator_finalize(&it);
    }

    if (!duplicate)
    {
        htable->size++;
        arc_slist_push_front(list, &node);
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

void * arc_htable_retrieve(struct arc_htable * htable, void * key)
{
    arc_hkey_t hvalue;
    arc_slist_t list;
    void *data = NULL;

    hvalue = htable->hash_fn(key, htable->key_size) % htable->num_buckets;
    list = htable->buckets[hvalue];

    if (list != NULL)
    {
        /* TODO: Optimize by creating stack iterators */
        struct arc_iterator it;
        arc_iterator_initialize(&it, list);

        arc_slist_before_begin(&it);

        while(arc_slist_next(&it))
        {
            struct arc_htable_node * node = arc_slist_data(&it);
            if(memcmp(node->key, key, htable->key_size) == 0)
            {
                data = node->data;
                break;
            }
        }

        arc_iterator_finalize(&it);
    }

    return data;
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
        arc_slist_t list = htable->buckets[i];
        if (list != NULL)
        {
            struct arc_iterator it;
            arc_iterator_initialize(&it, list);

            arc_slist_before_begin(&it);

            while(arc_slist_next(&it))
            {
                struct arc_htable_node * node = arc_slist_data(&it);
                free(node->key);
                free(node->data);
            }

            arc_iterator_finalize(&it);

            arc_slist_destroy(list);

            htable->buckets[i] = NULL;
        }
    }

    htable->size = 0;
}

/******************************************************************************/

void arc_htable_remove(struct arc_htable * htable, void * key)
{
    arc_hkey_t hvalue;
    arc_slist_t list;

    hvalue = htable->hash_fn(key, htable->key_size) % htable->num_buckets;
    list = htable->buckets[hvalue];

    if (list != NULL)
    {
        struct arc_iterator it, it_prev;
        arc_iterator_initialize(&it, list);
        arc_iterator_initialize(&it_prev, list);

        arc_slist_before_begin(&it);
        arc_slist_before_begin(&it_prev);

        while(arc_slist_next(&it))
        {
            struct arc_htable_node * node = arc_slist_data(&it);
            if(memcmp(node->key, key, htable->key_size) == 0)
            {
                free(node->key);
                free(node->data);
                arc_slist_erase_after(&it_prev);
                break;
            }

            arc_slist_next(&it_prev);
        }

        arc_iterator_finalize(&it);
        arc_iterator_finalize(&it_prev);
    }


}

/******************************************************************************/

int arc_htable_rehash(struct arc_htable * htable, size_t num_buckets)
{
    size_t i;
    arc_slist_t *buckets = malloc(sizeof(arc_slist_t) * num_buckets);

    if (buckets == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    for (i = 0; i < num_buckets; i++)
    {
        buckets[i] = arc_slist_create(sizeof(struct arc_htable_node));
    }

    for (i = 0; i < htable->num_buckets; i++)
    {
        arc_hkey_t hvalue ;

        if (arc_slist_size(htable->buckets[i]) > 0)
        {
            struct arc_iterator it;
            arc_iterator_initialize(&it, htable->buckets[i]);

            arc_slist_before_begin(&it);

            while(arc_slist_next(&it))
            {
                struct arc_htable_node * node = arc_slist_data(&it);

                hvalue = htable->hash_fn(node->key, htable->key_size) %
                         num_buckets;

                arc_slist_push_front(buckets[hvalue], node);
            }

            arc_iterator_finalize(&it);
        }

        arc_slist_destroy(htable->buckets[i]);
    }

    free(htable->buckets);
    htable->buckets = buckets;
    htable->num_buckets = num_buckets;

    return ARC_SUCCESS;
}

/******************************************************************************/
