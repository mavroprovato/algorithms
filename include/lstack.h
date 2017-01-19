#ifndef _LINKED_STACK_H
#define _LINKED_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "llist.h"

/**
 * A stack data structure, backed by a linked list.
 */
typedef struct {
    /** The linked list. */
    LList *ll;
    /** The stack size. */
    size_t size;
} LStack;

/**
 * Initialize the stack data structure.
 *
 * @param ls Pointer to the stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool ls_init(LStack *ls);

/**
 * Frees resources associated with the stack data structure.
 *
 * @param ls Pointer to the stack data structure to be freed.
 */
void ls_destroy(LStack *ls);

/**
 * Check if the stack contains any elements.
 *
 * @param ls Pointer to the stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool ls_is_empty(LStack *ls);

/**
 * Return the size of the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The size of the stack.
 */
size_t ls_size(LStack *ls);

/**
 * Add an element to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @param item Pointer to the item to add to the stack.
 */
bool ls_push(LStack *ls, void *item);

/**
 * Removes and returns the last element that was added to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *ls_pop(LStack *ls);

/**
 * Returns the last element that was added to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *ls_peek(LStack *ls);

/**
 * Traverse all the items of the stack and call a function for each of them.
 *
 * @param ls Pointer to the stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ls_foreach(LStack *ls, ITERATOR_FUNC iterator_func, void *data);

#endif // _LINKED_STACK_H
