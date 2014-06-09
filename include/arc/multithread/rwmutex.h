/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @author Anil M. Mahtani Mirchandani
 * @file rwmutex.h
 */

#ifndef ARC_RWMUTEX_H_
#define ARC_RWMUTEX_H_

typedef struct arc_rwmutex * arc_rwmutex_t;

/**
 * @name Create rwmutex
 */
arc_rwmutex_t arc_rwmutex_create(void);
/**
 *
 */
void arc_rwmutex_destroy(arc_rwmutex_t mutex) ;
/**
 *
 */
int arc_rwmutex_rlock(arc_rwmutex_t mutex);
/**
 *
 */
int arc_rwmutex_wlock(arc_rwmutex_t mutex);
/**
 *
 */
int arc_rwmutex_runlock(arc_rwmutex_t mutex);
/**
 *
 */
int arc_rwmutex_wunlock(arc_rwmutex_t mutex);

#endif