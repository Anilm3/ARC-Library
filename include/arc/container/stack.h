/*******************************************************************************
* Copyright (C) 2014 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)      *
*                                                                              *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>*
* This is free software: you are free to change and redistribute it.           *
* There is NO WARRANTY, to the extent permitted by law.                        *
*                                                                              *
*******************************************************************************/
/**
 * @file stack.h
 * @author Anil M. Mahtani Mirchandani
 * @date June, 2014
 *
 * @brief Stack
 *
 * A stack is very similar to a singly-linked list but it uses a bit less memory
 * and the operations require less instructions to be performed. The main goal
 * of this redundancy is for performance and experimentation purposes as the 
 * simplicity of the structure provides less instructions per operation thus 
 * making it easier to implement to be lock-free and thread-safe.
 *
 * @see http://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */

#ifndef ARC_STACK_H_
#define ARC_STACK_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif 

/**
 * @typedef arc_stack_t
 * @brief Stack definition
 *
 * The stack is defined as a pointer to be used with the creation and destruction
 * functions, direct stack allocations are not allowed.
 */
typedef struct arc_stack * arc_stack_t;

/**
 * @brief Creates a new stack
 *
 * The memory is allocated in the heap and has to be destroyed by the user. The 
 * data size provided has to coincide with the element type size to be used in
 * the container. 
 *
 * @param[in] data_size Size of the data element
 * @return New empty stack
 * @retval NULL if memory cannot be allocated
 */
arc_stack_t arc_stack_create(size_t data_size);
/**
 * @brief Destroys the memory associated to a stack 
 *
 * @param[in] stack Stack to perform the operation on
 */
void arc_stack_destroy(arc_stack_t stack);
/**
 * @brief Adds a new element to the front of the stack
 *
 * @param[in] stack Stack to perform the operation on
 * @param[in] data Data associated to the new element
 * @retval ARC_OUT_OF_MEMORY If memory could not be allocated
 * @retval ARC_SUCCESS If the element was added successfully
 */
int arc_stack_push(arc_stack_t stack, void * data);
/**
 * @brief Removes the first element from the stack
 *
 * @param[in] stack Stack to perform the operation on
 */
void arc_stack_pop(arc_stack_t stack);
/**
 * @brief Returns the data of the initial element of the stack
 *
 * @param[in] stack Stack to perform the operation on
 * @return Data pointer of the first element
 */
void * arc_stack_top(arc_stack_t stack);
/**
 * @brief Returns whether the stack is empty or not
 *
 * @param[in] stack Stack to perform the operation on
 * @retval 0 If the stack is not empty
 * @retval 1 If the stack is empty
 */
int arc_stack_empty(arc_stack_t stack);
/**
 * @brief Returns the size of the stack
 *
 * @param[in] stack Stack to perform the operation on
 * @return Size of the stack
 */
int arc_stack_size(arc_stack_t stack);
/**
 * @brief Clears the contents of the stack
 *
 * @param[in] stack Stack to perform the operation on
 */
void arc_stack_clear(arc_stack_t stack);

#ifdef __cplusplus
}
#endif

#endif