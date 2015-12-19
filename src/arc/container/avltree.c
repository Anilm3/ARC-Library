/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <arc/container/avltree.h>
#include <arc/common/defines.h>

#include <arc/container/avltree_def.h>
#include <arc/container/iterator_def.h>

#if 0
#define ARC_DEBUG(whatever) printf(whatever);fflush(stdout);
#define ARC_DEBUG1(whatever,whatever1) printf(whatever,whatever1);fflush(stdout);
#else
#define ARC_DEBUG(whatever)
#define ARC_DEBUG1(whatever,whatever1)
#endif

#define max(a,b) ((a) > (b) ? (a) : (b))
int arc_avltree_print_level(struct arc_avltree_node *node, int level)
{
    int result = 0;

    if (level == 0)
    {
        if (node != NULL)
        {
            printf("%u(%d) ", *((unsigned *)node->data), node->balance_factor);
            return 1;
        }
        else
        {
            printf("N ");
            return 0;
        }
    }

    if (node != NULL)
    {
        result += arc_avltree_print_level(node->left, level - 1);
        result += arc_avltree_print_level(node->right, level - 1);
    }
    else
    {
        result += arc_avltree_print_level(NULL, level - 1);
        result += arc_avltree_print_level(NULL, level - 1);
    }

    return result > 0;
}

void arc_avltree_print(struct arc_avltree *tree)
{
    int level = 0;
    printf("Printing tree\n- %d -\n", level);
    while (arc_avltree_print_level(tree->root, level++)) printf("\n- %d -\n", level);
    printf("\n");
}
        
/******************************************************************************/

struct arc_avltree * arc_avltree_create(size_t data_size, arc_cmp_fn_t cmp_fn)
{
    size_t aligned_size;
    struct arc_avltree * avltree = malloc(sizeof(struct arc_avltree));

    if (avltree == NULL)
    {
        return NULL;
    }

    /* The aligned size is the current size of the data block including the
       space occupied by the alignment */
    aligned_size = sizeof(struct arc_avltree_node) -
                   ARC_OFFSETOF(struct arc_avltree_node, data);

    aligned_size = (aligned_size > data_size ? 0 : data_size - aligned_size);

    avltree->root = NULL;
    avltree->size = 0;
    avltree->data_size = data_size;
    avltree->node_size = aligned_size + sizeof(struct arc_avltree_node);
    avltree->cmp_fn = cmp_fn;

    avltree->front.parent = NULL;
    avltree->front.left = NULL;
    avltree->front.right = NULL;

    avltree->back.parent = NULL;
    avltree->back.left = NULL;
    avltree->back.right = NULL;

    return avltree;
}

/******************************************************************************/

static void arc_avltree_free_node(struct arc_avltree_node *node)
{
    if (node->left != NULL)
    {
        arc_avltree_free_node(node->left);
    }

    if (node->right != NULL)
    {
        arc_avltree_free_node(node->right);
    }

    free(node);
}

/******************************************************************************/

void arc_avltree_destroy(struct arc_avltree *avltree)
{
    if (avltree->root != NULL)
    {
        arc_avltree_free_node(avltree->root);
    }

    free(avltree);
}

/******************************************************************************/
int arc_avltree_height(struct arc_avltree_node * node)
{
    int height = 0;

    if (node != NULL)
    {
        height += 1;
        height += max(arc_avltree_height(node->left),
                      arc_avltree_height(node->right));
    }

    return height;
}

static void arc_avltree_rotate(struct arc_avltree *avltree,
                               struct arc_avltree_node *node)
{
    struct arc_avltree_node **node_ref;

    if (node->parent == NULL)
    {
        node_ref = &(avltree->root);
    }
    else
    {
        node_ref = (node->parent->left == node ? &(node->parent->left) :
                                                 &(node->parent->right));
    }

    if (node->balance_factor == 1)
    {
        struct arc_avltree_node * child = node->right;
        if (child->balance_factor == 1)
        {
            ARC_DEBUG("Single Right rotation\n");
            child->parent = node->parent;
            node->right = child->left;
            if (node->right) node->right->parent = node;

            child->left = node;
            node->parent = child;
            node->balance_factor = 0;
            child->balance_factor = 0;
/*            node->balance_factor = arc_avltree_height(node->right) - */
                                   /*arc_avltree_height(node->left);*/
            /*child->balance_factor = arc_avltree_height(child->right) - */
                                    /*arc_avltree_height(child->left);*/
            *node_ref = child;
        }
        else
        {
            struct arc_avltree_node * grandchild = child->left;
            ARC_DEBUG("Double Right rotation\n");
            grandchild->parent = node->parent;
            child->parent = grandchild;
            node->parent = grandchild;
            node->right = grandchild->left;
            if (node->right) node->right->parent = node;
            child->left = grandchild->right;
            if (child->left) child->left->parent = child;
            grandchild->left = node;
            grandchild->right = child;
            /*node->balance_factor = arc_avltree_height(node->right) - */
                                   /*arc_avltree_height(node->left);*/
            if (grandchild->balance_factor != 0)
            {
                node->balance_factor = (grandchild->balance_factor == 1 ? -1 : 0);
                child->balance_factor =  (grandchild->balance_factor == 1 ? 0 : 1);
            }
            else
            {
                node->balance_factor = 0;
                child->balance_factor = 0;
            }
            /*child->balance_factor = arc_avltree_height(child->right) - */
                                    /*arc_avltree_height(child->left);*/
 /*(grandchild->balance_factor == 1 ? 0 : 1);*/
            grandchild->balance_factor = 0;
                                         /*arc_avltree_height(grandchild->right) - */
                                         /*arc_avltree_height(grandchild->left);*/
            *node_ref = grandchild;
        }
    }
    else
    {
        struct arc_avltree_node * child = node->left;
        
        if (child->balance_factor == 1)
        {
            struct arc_avltree_node * grandchild = child->right;
            ARC_DEBUG("Double Left rotation\n");
            grandchild->parent = node->parent;
            child->parent = grandchild;
            node->parent = grandchild;
            node->left = grandchild->right;
            if (node->left) node->left->parent = node;
            child->right = grandchild->left;
            if (child->right) child->right->parent = child;
            grandchild->left = child;
            grandchild->right = node;
            if (grandchild->balance_factor != 0)
            {
                node->balance_factor = (grandchild->balance_factor == 1 ? 0 : 1);
                child->balance_factor =  (grandchild->balance_factor == 1 ? -1 : 0);
            }
            else
            {
                node->balance_factor = 0;
                child->balance_factor = 0;
            }

  /*          node->balance_factor = arc_avltree_height(node->right) - */
                                   /*arc_avltree_height(node->left);*/
/*(grandchild->balance_factor == 1 ? 0 : 1);*/
    /*        child->balance_factor = arc_avltree_height(child->right) - */
                                    /*arc_avltree_height(child->left);*/
/*(grandchild->balance_factor == 1 ? -1 : 0);*/
            grandchild->balance_factor = 0;
                                         /*arc_avltree_height(grandchild->right) - */
                                         /*arc_avltree_height(grandchild->left);*/

            *node_ref = grandchild;
        }
        else
        {
            ARC_DEBUG("Single Left rotation\n");
            child->parent = node->parent;
            node->left = child->right;
            if (node->left) node->left->parent = node;
            child->right = node;
            node->parent = child;
            /*node->balance_factor = arc_avltree_height(node->right) - */
                                   /*arc_avltree_height(node->left);*/
            /*child->balance_factor = arc_avltree_height(child->right) - */
                                    /*arc_avltree_height(child->left);*/
            node->balance_factor = 0;
            child->balance_factor = 0;

            *node_ref = child;
        }
    }
}

int arc_avltree_insert(struct arc_avltree *avltree, void * data)
{
    struct arc_avltree_node *parent = NULL;
    struct arc_avltree_node *node = avltree->root;
    struct arc_avltree_node **node_ref = &(avltree->root);
    ARC_DEBUG1("Data %u\n", *((unsigned *)data));
    while (node != NULL)
    {
        int cmp_result = (*avltree->cmp_fn)(node->data, data);
        
        ARC_DEBUG1("Root %u\n", *((unsigned *)node->data));
        if (cmp_result == -1)
        {
            parent = node;
            node_ref = &(node->right);
            node = node->right;
            ARC_DEBUG("Found right\n");
        }
        else if (cmp_result == 1)
        {
            parent = node;
            node_ref = &(node->left);
            node = node->left;
            ARC_DEBUG("Found left\n");
        }
        else
        {
            return ARC_DUPLICATE;
        }
    }

    node = malloc(avltree->node_size);

    if (node == NULL)
    {
        return ARC_OUT_OF_MEMORY;
    }

    node->parent = parent;
    node->left   = NULL;
    node->right  = NULL;
    node->balance_factor = 0;
    avltree->size++;

    memcpy(node->data, data, avltree->data_size);
    *node_ref = node;

    /* Backtrack and update balance factors */
    while (parent != NULL)
    {
        int factor = (parent->right == node ? 1 : -1);
        if (abs(parent->balance_factor + factor) == 2)
        {
            arc_avltree_rotate(avltree, parent);
            break;
        }
        parent->balance_factor += factor;

        if (parent->balance_factor == 0)
        {
            break;
        }
        node = parent;
        parent = parent->parent;
    }

    /*arc_avltree_print(avltree);*/
    return ARC_SUCCESS;
}

/******************************************************************************/

static struct arc_avltree_node * arc_avltree_find_node(struct arc_avltree *avltree,
                                                     void * data)
{
    struct arc_avltree_node *node = avltree->root;

    while (node != NULL)
    {
        int cmp_result = (*avltree->cmp_fn)((void *)node->data, data);
        if (cmp_result == -1)
        {
            node = node->right;
        }
        else if (cmp_result == 1)
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

int arc_avltree_find(struct arc_avltree *avltree, void * data)
{
    return (arc_avltree_find_node(avltree, data) != NULL);
}

/******************************************************************************/

static void arc_avltree_remove_node(struct arc_avltree *avltree,
                                   struct arc_avltree_node *node)
{
    struct arc_avltree_node **node_ref;

    if (node->parent == NULL)
    {
        node_ref = &(avltree->root);
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
        struct arc_avltree_node * successor = arc_avltree_min(node->right);

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
    avltree->size--;
}

/******************************************************************************/

void arc_avltree_remove(struct arc_avltree *avltree, void * data)
{
    struct arc_avltree_node *node;

    node = arc_avltree_find_node(avltree, data);

    if (node == NULL)
    {
        return;
    }

    arc_avltree_remove_node(avltree, node);
}

/******************************************************************************/

static struct arc_avltree_node *arc_avltree_min(struct arc_avltree_node *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

/******************************************************************************/

static struct arc_avltree_node *arc_avltree_max(struct arc_avltree_node *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node;
}

/******************************************************************************/

int arc_avltree_empty(struct arc_avltree * avltree)
{
    return avltree->size == 0;
}

/******************************************************************************/

size_t arc_avltree_size(struct arc_avltree * avltree)
{
    return avltree->size;
}

/******************************************************************************/

void arc_avltree_clear(struct arc_avltree *avltree)
{
    arc_avltree_free_node(avltree->root);

    avltree->root = NULL;
    avltree->size = 0;
}

/******************************************************************************/

void arc_avltree_before_begin(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;

    avltree->front.parent = (avltree->root != NULL ?
                            arc_avltree_min(avltree->root) : NULL);

    it->node_ptr = &(avltree->front);
}

/******************************************************************************/

void arc_avltree_begin(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;

    avltree->front.parent = (avltree->root != NULL ?
                            arc_avltree_min(avltree->root) : NULL);

    it->node_ptr = avltree->front.parent;
}

/******************************************************************************/

void arc_avltree_end(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;

    avltree->back.parent = (avltree->root != NULL ?
                            arc_avltree_max(avltree->root) : NULL);

    it->node_ptr = avltree->back.parent;
}

/******************************************************************************/

void arc_avltree_after_end(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;

    avltree->back.parent = (avltree->root != NULL ?
                            arc_avltree_max(avltree->root) : NULL);

    it->node_ptr = &(avltree->back);
}

/******************************************************************************/

int arc_avltree_previous(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;
    struct arc_avltree_node * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->left == NULL)
        {
            it->node_ptr = &(avltree->front);
            return 0;
        }

        it->node_ptr = arc_avltree_max(node->left);
    }
    else
    {
        if (node->left != NULL)
        {
            it->node_ptr = arc_avltree_max(node->left);
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

            it->node_ptr = &(avltree->front);
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

int arc_avltree_next(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;
    struct arc_avltree_node * node = it->node_ptr;

    if (node == NULL)
    {
        return 0;
    }

    if (node->parent == NULL)
    {
        if (node->right == NULL)
        {
            it->node_ptr = &(avltree->back);
            return 0;
        }

        it->node_ptr = arc_avltree_min(node->right);
    }
    else
    {
        if (node->right != NULL)
        {
            it->node_ptr = arc_avltree_min(node->right);
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

            it->node_ptr = &(avltree->back);
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

void * arc_avltree_data(struct arc_iterator * it)
{
    struct arc_avltree_node * current = it->node_ptr;

    return &(current->data);
}

/******************************************************************************/

int arc_avltree_position(struct arc_iterator * it, void * data)
{
    struct arc_avltree * avltree = it->container;
    struct arc_avltree_node * node = arc_avltree_find_node(avltree, data);

    it->node_ptr = node;

    return (node != NULL);
}

/******************************************************************************/
void arc_avltree_erase(struct arc_iterator * it)
{
    struct arc_avltree * avltree = it->container;
    struct arc_avltree_node * current = it->node_ptr;

    if (it->node_ptr != (struct arc_avltree_node *)&(avltree->front) &&
        it->node_ptr != (struct arc_avltree_node *)&(avltree->back))
    {
        arc_avltree_remove_node(avltree, current);
    }
}

/******************************************************************************/
