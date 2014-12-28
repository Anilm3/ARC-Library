/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>

/* Sentinel node definition */
struct arc_bstree_snode
{
    struct arc_bstree_node * parent;
    struct arc_bstree_node * left;
    struct arc_bstree_node * right;
};

/* Standard node definition */
struct arc_bstree_node
{
    struct arc_bstree_node * parent;
    struct arc_bstree_node * left;
    struct arc_bstree_node * right;
    char data[1];
};

/* Container definition */
struct arc_bstree
{
    struct arc_bstree_node *root;
    struct arc_bstree_snode front;
    struct arc_bstree_snode back;
    size_t size;
    size_t data_size;
    size_t node_size;
    arc_cmp_fn_t cmp_fn;
};


static void arc_bstree_free_node_r(struct arc_bstree_node *node);