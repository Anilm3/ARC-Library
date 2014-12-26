/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <arc/container/bstree.h>
#include <arc/common/defines.h>

#include <arc/container/bstree_def.h>
#include <arc/container/iterator_def.h>

/******************************************************************************/

struct arc_bstree * arc_bstree_create(size_t data_size, arc_cmp_fn_t cmp_fn)
{
    size_t aligned_size;
    struct arc_bstree * bstree = malloc(sizeof(struct arc_bstree));

    if (bstree == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_bstree_node) -
                   ARC_OFFSETOF(struct arc_bstree_node, data);

    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    bstree->root = NULL;
    bstree->front = NULL;
    bstree->back = NULL;
    bstree->size = 0;
    bstree->data_size = data_size;
    bstree->node_size = aligned_size + sizeof(struct arc_bstree_node);
    bstree->cmp_fn = cmp_fn;

    return bstree;
}

/******************************************************************************/

static void arc_bstree_free_node_r(struct arc_bstree_node *node)
{
    if (node->left != NULL)
    {
        arc_bstree_free_node_r(node->left);
    }

    if (node->right != NULL)
    {
        arc_bstree_free_node_r(node->right);
    }

    free(node);
}

/******************************************************************************/

void arc_bstree_destroy(struct arc_bstree *bstree)
{
    if (bstree->root != NULL)
    {
        arc_bstree_free_node_r(bstree->root);
    }

    free(bstree);
}

/******************************************************************************/

int arc_bstree_insert(arc_bstree_t bstree, void * data)
{
    unsigned int only_left = 1, only_right = 1;
    struct arc_bstree_node *node = bstree->root;

    if (node == NULL)
    {
        bstree->root = malloc(bstree->node_size);

        if (bstree->root == NULL)
        {
            return ARC_ERROR;
        }

        bstree->front = bstree->root;
        bstree->back = bstree->root;
        bstree->root->parent = NULL;
        bstree->root->left   = NULL;
        bstree->root->right  = NULL;
        bstree->size++;

        memcpy(bstree->root->data, data, bstree->data_size);

        return ARC_SUCCESS;
    }

    while (1)
    {
        if ((*bstree->cmp_fn)((void *)node->data, data))
        {
            if (node->right != NULL)
            {
                node = node->right;
                only_right &= 1;
                only_left &= 0;
                continue;
            }

            node->right = malloc(bstree->node_size);

            if (node->right == NULL)
            {
                return ARC_ERROR;
            }

            node->right->parent = node;
            node->right->left   = NULL;
            node->right->right  = NULL;

            bstree->size++;

            memcpy(node->right->data, data, bstree->data_size);

            if (only_right)
            {
                bstree->front = node;
            }

            break;
        }
        else if ((*bstree->cmp_fn)(data, (void *)node->data))
        {
            if (node->left != NULL)
            {
                node = node->left;
                only_right &= 0;
                only_left &= 1;
                continue;
            }

            node->left = malloc(bstree->node_size);

            if (node->left == NULL)
            {
                return ARC_ERROR;
            }

            node->left->parent = node;
            node->left->left   = NULL;
            node->left->right  = NULL;

            bstree->size++;

            memcpy(node->left->data, data, bstree->data_size);

            if (only_left)
            {
                bstree->front = node;
            }

            break;
        }
        else
        {
            return ARC_DUPLICATE;
        }
    }

    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_bstree_empty(struct arc_bstree * bstree)
{
    return bstree->size == 0;
}

/******************************************************************************/

size_t arc_bstree_size(struct arc_bstree * bstree)
{
    return bstree->size;
}

/******************************************************************************/

void arc_bstree_clear(struct arc_bstree *bstree)
{
    arc_bstree_free_node_r(bstree->root);

    bstree->root = NULL;
    bstree->front = NULL;
    bstree->back = NULL;
    bstree->size = 0;
}

/******************************************************************************/