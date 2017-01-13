#ifndef _LINKED_STACK_H
#define _LINKED_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "linked_list.h"

/**
 * A stack data structure, backed by a linked list.
 */
typedef struct {
    /** The linked list. */
    LinkedList *ll;
    /** The stack size. */
    size_t size;
} LinkedStack;

/**
 * Initialize the stack data structure.
 *
 * @param ls Pointer to the stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool ls_init(LinkedStack *ls);

/**
 * Frees resources associated with the stack data structure.
 *
 * @param ls Pointer to the stack data structure to be freed.
 */
void ls_destroy(LinkedStack *ls);

/**
 * Check if the stack contains any elements.
 *
 * @param ls Pointer to the stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool ls_is_empty(LinkedStack *ls);

/**
 * Return the size of the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The size of the stack.
 */
size_t ls_size(LinkedStack *ls);

/**
 * Add an element to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @param item Pointer to the item to add to the stack.
 */
bool ls_push(LinkedStack *ls, void *item);

/**
 * Removes and returns the last element that was added to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *ls_pop(LinkedStack *ls);

/**
 * Returns the last element that was added to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *ls_peek(LinkedStack *ls);

/**
 * Traverse all the items of the stack and call a function for each of them.
 *
 * @param ls Pointer to the stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ls_foreach(LinkedStack *ls, ITERATOR_FUNC iterator_func, void *data);

#endif // _LINKED_STACK_H
