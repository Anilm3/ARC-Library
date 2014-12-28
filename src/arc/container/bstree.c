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
    bstree->size = 0;
    bstree->data_size = data_size;
    bstree->node_size = aligned_size + sizeof(struct arc_bstree_node);
    bstree->cmp_fn = cmp_fn;

    bstree->front.parent = NULL;
    bstree->front.left = NULL;
    bstree->front.right = NULL;

    bstree->back.parent = NULL;
    bstree->back.left = NULL;
    bstree->back.right = NULL;

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

#if 0
static int arc_bstree_insert_node_r(struct arc_bstree *bstree,
                                    struct arc_bstree_node *parent,
                                    struct arc_bstree_node **node,
                                    void * data)
{
    if (*node == NULL)
    {
        *node = malloc(bstree->node_size);

        if (*node == NULL)
        {
            return ARC_ERROR;
        }

        (*node)->parent = parent;
        (*node)->left   = NULL;
        (*node)->right  = NULL;
        bstree->size++;

        memcpy((*node)->data, data, bstree->data_size);

        return ARC_SUCCESS;
    }


    if ((*bstree->cmp_fn)((void *)(*node)->data, data))
    {
        return arc_bstree_insert_node_r(bstree, *node, &(*node)->right, data);
    }
    else if ((*bstree->cmp_fn)(data, (void *)(*node)->data))
    {
        return arc_bstree_insert_node_r(bstree, *node, &(*node)->left, data);
    }
    else
    {
        return ARC_DUPLICATE;
    }
}

int arc_bstree_insert(struct arc_bstree *bstree, void * data)
{
    return arc_bstree_insert_node_r(bstree, NULL, &bstree->root, data);
#else

int arc_bstree_insert(struct arc_bstree *bstree, void * data)
{
    unsigned left_only = 1, right_only = 1;
    struct arc_bstree_node *node = bstree->root;

    if (node == NULL)
    {
        bstree->root = malloc(bstree->node_size);

        if (bstree->root == NULL)
        {
            return ARC_ERROR;
        }

        bstree->front.parent = bstree->root;
        bstree->back.parent = bstree->root;
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
                left_only = 0;
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

            if (right_only)
            {
                bstree->back.parent = node->right;
            }

            break;
        }
        else if ((*bstree->cmp_fn)(data, (void *)node->data))
        {
            if (node->left != NULL)
            {
                node = node->left;
                right_only = 0;
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

            if (left_only)
            {
                bstree->front.parent = node->left;
            }

            break;
        }
        else
        {
            return ARC_DUPLICATE;
        }
    }

    return ARC_SUCCESS;
#endif
}

/******************************************************************************/

int arc_bstree_find(struct arc_bstree *bstree, void * data)
{
    struct arc_bstree_node *node = bstree->root;

    while (node != NULL)
    {
        if ((*bstree->cmp_fn)((void *)node->data, data))
        {
            node = node->right;
        }
        else if ((*bstree->cmp_fn)(data, (void *)node->data))
        {
            node = node->left;
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

/******************************************************************************/
#if 0
static struct arc_bstree_node *arc_bstree_min(struct arc_bstree_node *node)
{
    if (node->left != NULL)
    {
        return arc_bstree_min(node->left);
    }

    return node;
}
#else
static struct arc_bstree_node *arc_bstree_min(struct arc_bstree_node *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}
#endif
/******************************************************************************/
#if 0
static struct arc_bstree_node *arc_bstree_max(struct arc_bstree_node *node)
{
    if (node->right != NULL)
    {
        return arc_bstree_max(node->right);
    }

    return node;
}
#else
static struct arc_bstree_node *arc_bstree_max(struct arc_bstree_node *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node;
}
#endif
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
    bstree->size = 0;
}

/******************************************************************************/

void arc_bstree_before_begin(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    it->node_ptr = &(bstree->front);
}

/******************************************************************************/

void arc_bstree_begin(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    it->node_ptr = bstree->front.parent;
}

/******************************************************************************/

void arc_bstree_end(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    it->node_ptr = bstree->back.parent;
}

/******************************************************************************/

void arc_bstree_after_end(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    it->node_ptr = &(bstree->back);
}

/******************************************************************************/

int arc_bstree_previous(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->left == NULL)
        {
            it->node_ptr = &(bstree->front);
            return 0;
        }

        it->node_ptr = arc_bstree_max(node->left);
    }
    else
    {
        if (node->left != NULL)
        {
            it->node_ptr = arc_bstree_max(node->left);
        }
        else if (node == node->parent->left)
        {
            if (node->parent->parent == NULL)
            {
                it->node_ptr = &(bstree->front);
                return 0;
            }

            if (node->parent == node->parent->parent->right)
            {
                it->node_ptr = node->parent->parent;
            }
            else
            {
                it->node_ptr = &(bstree->front);
                return 0;
            }
        }
        else /*if (node == node->parent->right)*/
        {
            it->node_ptr = node->parent;
        }
    }

    return 1;
}
/******************************************************************************/

int arc_bstree_next(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->right == NULL)
        {
            it->node_ptr = &(bstree->back);
            return 0;
        }

        it->node_ptr = arc_bstree_min(node->right);
    }
    else
    {
        if (node->right != NULL)
        {
            it->node_ptr = arc_bstree_min(node->right);
        }
        else if (node == node->parent->right)
        {
            if (node->parent->parent == NULL)
            {
                it->node_ptr = &(bstree->back);
                return 0;
            }

            if (node->parent == node->parent->parent->left)
            {
                it->node_ptr = node->parent->parent;
            }
            else
            {
                it->node_ptr = &(bstree->back);
                return 0;
            }
        }
        else /*if (node == node->parent->left)*/
        {
            it->node_ptr = node->parent;
        }
    }

    return 1;
}

/******************************************************************************/

void * arc_bstree_data(struct arc_iterator * it)
{
    struct arc_bstree_node * current = it->node_ptr;

    return &(current->data);
}

/******************************************************************************/