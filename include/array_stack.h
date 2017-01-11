#ifndef _ARRAY_STACK_H
#define _ARRAY_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "util.h"

/**
 * The stack data structure, backed by an array.
 */
typedef struct {
    /** The stack elements. */
    void **items;
    /** The stack size. */
    size_t size;
    /** The current capacity of the stack */
    size_t capacity;
} ArrayStack;

/**
 * Initialize the stack data structure.
 *
 * @param as Pointer to the stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool as_init(ArrayStack *as);

/**
 * Frees resources associated with the array stack data structure.
 *
 * @param as Pointer to the array stack data structure to be freed.
 */
void as_destroy(ArrayStack *as);

/**
 * Check if the stack contains any elements.
 *
 * @param as Pointer to the array stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool as_is_empty(ArrayStack *as);

/**
 * Return the size of the array stack.
 *
 * @param as Pointer to the array stack data structure.
 * @return The size of the array stack.
 */
size_t as_size(ArrayStack *as);

/**
 * Add an element to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @param item Pointer to the item to add to the stack.
 */
bool as_push(ArrayStack *as, void *item);

/**
 * Removes and returns the last element that was added to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *as_pop(ArrayStack *as);

/**
 * Returns the last element that was added to the stack.
 *
 * @param as Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *as_peek(ArrayStack *as);

/**
 * Traverse all the items of the stack and call a function for each of them.
 *
 * @param as Pointer to the stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void as_foreach(ArrayStack *as, ITERATOR_FUNC iterator_func, void *data);

#endif // _ARRAY_STACK_H
