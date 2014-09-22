/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/

#include <stdlib.h>
#include <pthread.h>

#include <arc/common/defines.h>
#include <arc/multithread/rwmutex.h>

struct arc_rwmutex
{
    int readers_reading;
    int writer_writing;
    int writer_waiting;
    pthread_mutex_t mutex;
    pthread_cond_t cond_var;
};

/******************************************************************************/

struct arc_rwmutex * arc_rwmutex_create()
{
    struct arc_rwmutex * rwmutex = malloc(sizeof(struct arc_rwmutex));

    if (rwmutex == NULL)
    {
        return NULL;
    }

    rwmutex->readers_reading = 0;
    rwmutex->writer_writing = 0;
    rwmutex->writer_waiting = 0;
    
    pthread_mutex_init(&rwmutex->mutex, NULL);
    pthread_cond_init(&(rwmutex->cond_var), NULL);
    
    return rwmutex;
}

/******************************************************************************/

void arc_rwmutex_destroy(struct arc_rwmutex * rwmutex)
{
    pthread_cond_destroy(&(rwmutex->cond_var));
    pthread_mutex_destroy(&(rwmutex->mutex));
    
    free(rwmutex);
}

/******************************************************************************/

int arc_rwmutex_rlock(struct arc_rwmutex * rwmutex)
{
    pthread_mutex_lock(&(rwmutex->mutex));
    
    while (rwmutex->writer_writing || rwmutex->writer_waiting) 
    {
        pthread_cond_wait(&(rwmutex->cond_var), &(rwmutex->mutex));
    }
    
    rwmutex->readers_reading++;

    pthread_mutex_unlock(&(rwmutex->mutex));
    
    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_rwmutex_wlock(struct arc_rwmutex * rwmutex)
{
    pthread_mutex_lock(&(rwmutex->mutex));
    
    rwmutex->writer_waiting++;
    
    while (rwmutex->writer_writing || 
           rwmutex->writer_waiting > 1 || 
           rwmutex->readers_reading ) 
    {
        pthread_cond_wait(&(rwmutex->cond_var), &(rwmutex->mutex));
    }
    
    rwmutex->writer_writing++;
    rwmutex->writer_waiting--;

    pthread_mutex_unlock(&(rwmutex->mutex));
    
    return ARC_SUCCESS;
}

/******************************************************************************/

int arc_rwmutex_runlock(struct arc_rwmutex * rwmutex)
{
    pthread_mutex_lock(&(rwmutex->mutex));
    
    if (rwmutex->readers_reading == 0)
    {
        pthread_mutex_unlock(&(rwmutex->mutex));

        return ARC_ERROR;
    }
    
    rwmutex->readers_reading--;
    
    if (rwmutex->readers_reading == 0)
    {
        pthread_cond_signal(&(rwmutex->cond_var));
    }
    
    pthread_mutex_unlock(&(rwmutex->mutex));
    
    return ARC_SUCCESS;

}

/******************************************************************************/

int arc_rwmutex_wunlock(struct arc_rwmutex * rwmutex)
{
    pthread_mutex_lock(&(rwmutex->mutex));
    
    if (rwmutex->writer_writing == 0)
    {
        pthread_mutex_unlock(&(rwmutex->mutex));

        return ARC_ERROR;
    }

    rwmutex->writer_writing = 0;

    pthread_cond_broadcast(&(rwmutex->cond_var));

    pthread_mutex_unlock(&(rwmutex->mutex));

    return ARC_SUCCESS;
}

/******************************************************************************/
