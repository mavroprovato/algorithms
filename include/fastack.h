#ifndef _FA_STACK_H
#define _FA_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"

/**
 * A stack data structure, backed by an array.
 */
typedef struct {
    /** The stack elements. */
    void **items;
    /** The stack size. */
    size_t size;
    /** The current capacity of the stack. */
    size_t capacity;
} FAStack;

/**
 * Initialize the fixed array stack data structure.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @param capacity The stack capacity.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool fas_init(FAStack *fas, size_t capacity);

/**
 * Frees resources associated with the fixed array stack data structure.
 *
 * @param fas Pointer to the fixed array stack data structure to be freed.
 */
void fas_destroy(FAStack *fas);

/**
 * Check if the fixed array stack contains any elements.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool fas_is_empty(FAStack *fas);

/**
 * Return the size of the fixed array stack.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @return The size of the fixed array stack.
 */
size_t fas_size(FAStack *fas);

/**
 * Add an element to the fixed array stack. Note that NULL elements cannot be
 * added to the stack.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @return true if the element was pushed successfully, false otherwise.
 */
bool fas_push(FAStack *fas, void *item);

/**
 * Removes and returns the last element that was added to the fixed array stack.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @return The last element that was added to the fixed array stack, or NULL if
 * the stack was empty.
 */
void *fas_pop(FAStack *fas);

/**
 * Returns the last element that was added to the fixed array stack.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @return The last element that was added to the fixed array stack, or NULL if
 * the stack was empty.
 */
void *fas_peek(FAStack *fas);

/**
 * Traverse all the items of the fixed array stack and call a function for each
 * of them.
 *
 * @param fas Pointer to the fixed array stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void fas_foreach(FAStack *fas, ITERATOR_FUNC iterator_func, void *data);

#endif // _FA_STACK_H
