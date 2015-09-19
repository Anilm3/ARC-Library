/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @addtogroup Queue
 * @{
 *
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 * @ingroup Container
 *
 * @brief Queue
 *
 * A queue is very similar to a singly-linked list but it uses a bit less memory
 * and the operations require less instructions to be performed. The main goal
 * of this redundancy is for performance and experimentation purposes as the
 * simplicity of the structure provides less instructions per operation thus
 * making it easier to implement to be lock-free and thread-safe.
 *
 * For more information and examples check the documentation (\ref page_queue).
 *
 * @see http://en.wikipedia.org/wiki/Queue_(data_structure)
 */

#ifndef ARC_QUEUE_H_
#define ARC_QUEUE_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @typedef arc_queue_t
 * @brief Queue definition
 *
 * The queue is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_queue * arc_queue_t;

/**
 * @brief Creates a new queue
 *
 * The memory is allocated in the heap and has to be destroyed by the user. The
 * data size provided has to coincide with the element type size to be used in
 * the container.
 *
 * @param[in] data_size Size of the data element
 * @return New empty queue
 * @retval NULL if memory cannot be allocated
 */
arc_queue_t arc_queue_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a queue
 *
 * @param[in] queue Queue to perform the operation on
 */
void arc_queue_destroy(arc_queue_t queue);
/**
 * @brief Adds a new element to the front of the queue
 *
 * @param[in] queue Queue to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_queue_push(arc_queue_t queue, void * data);
/**
 * @brief Removes the first element from the queue
 *
 * @param[in] queue Queue to perform the operation on
 */
void arc_queue_pop(arc_queue_t queue);
/**
 * @brief Returns the data of the initial element of the queue
 *
 * @param[in] queue Queue to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_queue_front(arc_queue_t queue);
/**
 * @brief Returns the data of the last element of the queue
 *
 * @param[in] queue Queue to perform the operation on
 * @return Data pointer of the last element
 */
void * arc_queue_back(arc_queue_t queue);
/**
 * @brief Returns whether the queue is empty or not
 *
 * @param[in] queue Queue to perform the operation on
 * @retval 0 If the queue is not empty
 * @retval 1 If the queue is empty
 */
int arc_queue_empty(arc_queue_t queue);
/**
 * @brief Returns the size of the queue
 *
 * @param[in] queue Queue to perform the operation on
 * @return Size of the queue
 */
int arc_queue_size(arc_queue_t queue);
/**
 * @brief Clears the contents of the queue
 *
 * @param[in] queue Queue to perform the operation on
 */
void arc_queue_clear(arc_queue_t queue);

#ifdef __cplusplus
}
#endif

#endif /* ARC_QUEUE_H_ */

/** @} */
