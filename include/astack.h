#ifndef _A_STACK_H
#define _A_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "util.h"

/**
 * A stack data structure, backed by an array.
 */
typedef struct {
    /** The stack elements. */
    void **items;
    /** The stack size. */
    size_t size;
    /** The current capacity of the stack */
    size_t capacity;
} AStack;

/**
 * Initialize the stack data structure.
 *
 * @param as Pointer to the stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool as_init(AStack *as);

/**
 * Frees resources associated with the array stack data structure.
 *
 * @param as Pointer to the array stack data structure to be freed.
 */
void as_destroy(AStack *as);

/**
 * Check if the stack contains any elements.
 *
 * @param as Pointer to the array stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool as_is_empty(AStack *as);

/**
 * Return the size of the array stack.
 *
 * @param as Pointer to the array stack data structure.
 * @return The size of the array stack.
 */
size_t as_size(AStack *as);

/**
 * Add an element to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @param item Pointer to the item to add to the stack.
 */
bool as_push(AStack *as, void *item);

/**
 * Removes and returns the last element that was added to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *as_pop(AStack *as);

/**
 * Returns the last element that was added to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *as_peek(AStack *as);

/**
 * Traverse all the items of the stack and call a function for each of them.
 *
 * @param as Pointer to the stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void as_foreach(AStack *as, ITERATOR_FUNC iterator_func, void *data);

#endif // _A_STACK_H
