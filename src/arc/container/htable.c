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


#include <stdlib.h>
#include <string.h>
#include <arc/common/defines.h>
#include <arc/type/function.h>
#include <arc/container/htable.h>
#include <arc/container/slist.h>
#include <arc/container/htable_def.h>

struct arc_htable * arc_htable_create(size_t key_size,
                                      size_t data_size,
                                      arc_hash_fn_t hash_fn)
{
    int i;
    struct arc_htable * htable = malloc(sizeof(struct arc_htable));

    htable->data_size = data_size;
    htable->key_size = key_size;
    htable->size = 0;
    htable->hash_fn = hash_fn;

    for (i = 0; i < NUM_BUCKETS; i++)
    {
        htable->buckets[i] = NULL;
    }

    return htable;
}

void arc_htable_destroy(struct arc_htable * htable)
{
    arc_htable_clear(htable);

    free(htable);
}

int arc_htable_insert(struct arc_htable * htable, void * key, void * data)
{
    unsigned long hvalue = htable->hash_fn(key) % NUM_BUCKETS;
    arc_slist_t list = htable->buckets[hvalue];
    struct arc_htable_node node;
    int duplicate = 0;
    
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

    if (list == NULL)
    {
        list = arc_slist_create(sizeof(struct arc_htable_node));
        htable->buckets[hvalue] = list;
    }
    else
    {
        /* TODO: Optimize by creating stack iterators */
        arc_iterator_t it = arc_iterator_create(list);

        arc_slist_before_begin(it);

        while(arc_slist_next(it))
        {
            struct arc_htable_node * list_node = arc_slist_data(it);
            if(memcmp(list_node->key, key, htable->key_size) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        arc_iterator_destroy(it);
    }
    
    if (!duplicate)
    {
        htable->size++;
        arc_slist_push_front(list, &node);
    }

    return ARC_SUCCESS;
}

void * arc_htable_retrieve(struct arc_htable * htable, void * key)
{
    unsigned long hvalue = htable->hash_fn(key) % NUM_BUCKETS;
    arc_slist_t list = htable->buckets[hvalue];
    void *data = NULL;

    if (list != NULL)
    {
        /* TODO: Optimize by creating stack iterators */
        arc_iterator_t it = arc_iterator_create(list);

        arc_slist_before_begin(it);

        while(arc_slist_next(it))
        {
            struct arc_htable_node * node = arc_slist_data(it);
            if(memcmp(node->key, key, htable->key_size) == 0)
            {
                data = node->data;
                break;
            }
        }

        arc_iterator_destroy(it);
    }
    
    return data;
}

int arc_htable_empty(struct arc_htable * htable)
{
    return (htable->size == 0);
}

size_t arc_htable_size(struct arc_htable * htable)
{
    return htable->size;
}

void arc_htable_clear(struct arc_htable * htable)
{
    int i;

    for (i = 0; i < NUM_BUCKETS; i++)
    {
        arc_slist_t list = htable->buckets[i];
        if (list != NULL)
        {
            arc_iterator_t it = arc_iterator_create(list);

            arc_slist_before_begin(it);

            while(arc_slist_next(it))
            {
                struct arc_htable_node * node = arc_slist_data(it);
                free(node->key);
                free(node->data);
            }

            arc_iterator_destroy(it);

            arc_slist_destroy(list);

            htable->buckets[i] = NULL;
        }
    }

    htable->size = 0;
}

void arc_htable_remove(struct arc_htable * htable, void * key)
{
    unsigned long hvalue = htable->hash_fn(key) % NUM_BUCKETS;
    arc_slist_t list = htable->buckets[hvalue];

    if (list != NULL)
    {
        arc_iterator_t it = arc_iterator_create(list);
        arc_iterator_t it_prev = arc_iterator_create(list);

        arc_slist_before_begin(it);
        arc_slist_before_begin(it_prev);

        while(arc_slist_next(it))
        {
            struct arc_htable_node * node = arc_slist_data(it);
            if(memcmp(node->key, key, htable->key_size) == 0)
            {
                free(node->key);
                free(node->data);
                arc_slist_erase_after(it_prev);
                break;
            }

            arc_slist_next(it_prev);
        }

        arc_iterator_destroy(it);
        arc_iterator_destroy(it_prev);
    }
    
 
}


