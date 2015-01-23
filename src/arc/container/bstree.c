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

static void arc_bstree_free_node(struct arc_bstree_node *node)
{
    if (node->left != NULL)
    {
        arc_bstree_free_node(node->left);
    }

    if (node->right != NULL)
    {
        arc_bstree_free_node(node->right);
    }

    free(node);
}

/******************************************************************************/

void arc_bstree_destroy(struct arc_bstree *bstree)
{
    if (bstree->root != NULL)
    {
        arc_bstree_free_node(bstree->root);
    }

    free(bstree);
}

/******************************************************************************/

int arc_bstree_insert(struct arc_bstree *bstree, void * data)
{
    struct arc_bstree_node *parent = NULL;
    struct arc_bstree_node *node = bstree->root;
    struct arc_bstree_node **node_ref = &(bstree->root);

    while (node != NULL)
    {
        if ((*bstree->cmp_fn)(node->data, data))
        {
            parent = node;
            node_ref = &(node->right);
            node = node->right;
        }
        else if ((*bstree->cmp_fn)(data, node->data))
        {
            parent = node;
            node_ref = &(node->left);
            node = node->left;
        }
        else
        {
            return ARC_DUPLICATE;
        }
    }

    node = malloc(bstree->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->parent = parent;
    node->left   = NULL;
    node->right  = NULL;
    bstree->size++;

    memcpy(node->data, data, bstree->data_size);

    *node_ref = node;

    return ARC_SUCCESS;
}

/******************************************************************************/

static struct arc_bstree_node * arc_bstree_find_node(struct arc_bstree *bstree,
                                                     void * data)
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
            return node;
        }
    }

    return NULL;
}

/******************************************************************************/

int arc_bstree_find(struct arc_bstree *bstree, void * data)
{
    return (arc_bstree_find_node(bstree, data) != NULL);
}

/******************************************************************************/

static void arc_bstree_remove_node(struct arc_bstree *bstree,
                                   struct arc_bstree_node *node)
{
    struct arc_bstree_node **node_ref;

    if (node->parent == NULL)
    {
        node_ref = &(bstree->root);
    }
    else if (node == node->parent->left)
    {
        node_ref = &(node->parent->left);
    }
    else
    {
        node_ref = &(node->parent->right);
    }

    /* Leaf node */
    if (node->left == NULL || node->right == NULL)
    {
        if (node->right != NULL)
        {
            *node_ref = node->right;
            node->right->parent = node->parent;
        }
        else if (node->left != NULL)
        {
            *node_ref = node->left;
            node->left->parent = node->parent;
        }
        else
        {
            *node_ref = NULL;
        }
    }
    else
    {
        struct arc_bstree_node * successor = arc_bstree_min(node->right);

        if (successor->parent->left == successor)
        {
            successor->parent->left = successor->right;
        }
        else
        {
            successor->parent->right = successor->right;
        }

        if (successor->right != NULL)
        {
            successor->right->parent = successor->parent;
        }

        successor->parent = node->parent;
        successor->right = node->right;
        successor->left = node->left;

        if (successor->right != NULL)
        {
            successor->right->parent = successor;
        }

        if (successor->left != NULL)
        {
            successor->left->parent = successor;
        }

        *node_ref = successor;
    }

    free(node);
    bstree->size--;
}

/******************************************************************************/

void arc_bstree_remove(struct arc_bstree *bstree, void * data)
{
    struct arc_bstree_node *node;

    node = arc_bstree_find_node(bstree, data);

    if (node == NULL)
    {
        return;
    }

    arc_bstree_remove_node(bstree, node);
}

/******************************************************************************/

static struct arc_bstree_node *arc_bstree_min(struct arc_bstree_node *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

/******************************************************************************/

static struct arc_bstree_node *arc_bstree_max(struct arc_bstree_node *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node;
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
    arc_bstree_free_node(bstree->root);

    bstree->root = NULL;
    bstree->size = 0;
}

/******************************************************************************/

void arc_bstree_before_begin(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->front.parent = (bstree->root != NULL ?
                            arc_bstree_min(bstree->root) : NULL);

    it->node_ptr = &(bstree->front);
}

/******************************************************************************/

void arc_bstree_begin(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->front.parent = (bstree->root != NULL ?
                            arc_bstree_min(bstree->root) : NULL);

    it->node_ptr = bstree->front.parent;
}

/******************************************************************************/

void arc_bstree_end(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->back.parent = (bstree->root != NULL ?
                            arc_bstree_max(bstree->root) : NULL);

    it->node_ptr = bstree->back.parent;
}

/******************************************************************************/

void arc_bstree_after_end(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;

    bstree->back.parent = (bstree->root != NULL ?
                            arc_bstree_max(bstree->root) : NULL);

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
            while (node->parent->parent != NULL)
            {
                if (node->parent == node->parent->parent->right)
                {
                    it->node_ptr = node->parent->parent;
                    return 1;
                }
                node = node->parent;
            }

            it->node_ptr = &(bstree->front);
            return 0;
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
            while (node->parent->parent != NULL)
            {
                if (node->parent == node->parent->parent->left)
                {
                    it->node_ptr = node->parent->parent;
                    return 1;
                }
                node = node->parent;
            }

            it->node_ptr = &(bstree->back);
            return 0;
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

void arc_bstree_erase(struct arc_iterator * it)
{
    struct arc_bstree * bstree = it->container;
    struct arc_bstree_node * current = it->node_ptr;

    if (it->node_ptr != (struct arc_bstree_node *)&(bstree->front) &&
        it->node_ptr != (struct arc_bstree_node *)&(bstree->back))
    {
        arc_bstree_remove_node(bstree, current);
    }
}

/******************************************************************************/
