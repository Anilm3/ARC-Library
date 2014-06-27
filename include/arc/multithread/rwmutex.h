/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file rwmutex.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Read-Write mutex
 *
 * Probably should move to pthread_rwlock_t for linux
 *
 * @see http://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock
 */

#ifndef ARC_RWMUTEX_H_
#define ARC_RWMUTEX_H_

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @typedef arc_rwmutex_t
 * @brief Read-Write mutex definition
 */
typedef struct arc_rwmutex * arc_rwmutex_t;

/**
 * @brief Creates a new mutex
 *
 * The memory is allocated in the heap and has to be destroyed by the user.
 *
 * @return New mutex
 * @retval NULL if memory cannot be allocated
 */
arc_rwmutex_t arc_rwmutex_create(void);
/**
 * @brief Destroys the memory associated to the mutex
 *
 * @param[in] mutex Mutex to perform the operation on
 */
void arc_rwmutex_destroy(arc_rwmutex_t mutex) ;
/**
 * @brief Reader lock for the mutex
 *
 * @param[in] mutex Mutex to perform the operation on
 * @retval ARC_SUCCESS if the mutex has been locked successfully
 */
int arc_rwmutex_rlock(arc_rwmutex_t mutex);
/**
 * @brief Writer lock for the mutex
 *
 * @param[in] mutex Mutex to perform the operation on
 * @retval ARC_SUCCESS if the mutex has been locked successfully
 */
int arc_rwmutex_wlock(arc_rwmutex_t mutex);
/**
 * @brief Reader unlock for the mutex
 *
 * @param[in] mutex Mutex to perform the operation on
 * @retval ARC_SUCCESS if the mutex has been unlocked successfully
 */
int arc_rwmutex_runlock(arc_rwmutex_t mutex);
/**
 * @brief Writer unlock for the mutex
 *
 * @param[in] mutex Mutex to perform the operation on
 * @retval ARC_SUCCESS if the mutex has been unlocked successfully
 */
int arc_rwmutex_wunlock(arc_rwmutex_t mutex);

#ifdef __cplusplus
}
#endif

#endif