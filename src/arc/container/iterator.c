/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <arc/container/iterator.h>
#include <arc/common/defines.h>

#include <arc/container/iterator_def.h>

/******************************************************************************/

int arc_iterator_initialize(struct arc_iterator *it, void *container)
{
    it->container = container;
    it->node_ptr = NULL;
    it->node_num = 0;
    it->node_idx = 0;

    return ARC_SUCCESS;
}

/******************************************************************************/

void arc_iterator_finalize(struct arc_iterator *it)
{
    it->container = NULL;
    it->node_ptr = NULL;
    it->node_num = 0;
    it->node_idx = 0;
}

/******************************************************************************/

struct arc_iterator * arc_iterator_create(void * container)
{
    struct arc_iterator * it = malloc(sizeof(struct arc_iterator));

    if (it == NULL)
    {
        return NULL;
    }

    arc_iterator_initialize(it, container);

    return it;
}
/******************************************************************************/

void arc_iterator_destroy(struct arc_iterator *it)
{
    arc_iterator_finalize(it);
    free(it);
}

/******************************************************************************/
