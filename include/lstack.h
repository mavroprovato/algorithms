#ifndef _L_STACK_H
#define _L_STACK_H

#include <stddef.h>
#include <stdbool.h>

#include "common.h"

/**
 * The linked stack node.
 */
typedef struct LStackNode {
    /** The item. */
    void *item;
    /** The next node. */
    struct LStackNode *next;
} LStackNode;

/**
 * A stack data structure, backed by a linked list.
 */
typedef struct {
    /** The head element. */
    LStackNode *head;
    /** The stack size. */
    size_t size;
} LStack;

/**
 * Initialize the linked stack data structure.
 *
 * @param ls Pointer to the linked stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool ls_init(LStack *ls);

/**
 * Frees resources associated with the linked stack data structure.
 *
  @param ls Pointer to the linked stack data structure to be freed.
 */
void ls_destroy(LStack *ls);

/**
 * Check if the stack contains any elements.
 *
 * @param ls Pointer to the linked stack data structure.
 * @return true if the linked stack contains elements, false otherwise.
 */
bool ls_is_empty(LStack *ls);

/**
 * Return the size of the linked stack.
 *
 * @param ls Pointer to the linked stack data structure.
 * @return The size of the linked stack.
 */
size_t ls_size(LStack *ls);

/**
 * Add an element to the linked stack. Note that NULL elements cannot be added
 * to the stack.
 *
 * @param ls Pointer to the linked stack data structure.
 * @param item Pointer to the item to add to the linked stack.
 */
bool ls_push(LStack *ls, void *item);

/**
 * Removes and returns the last element that was added to the linked stack.
 *
 * @param ls Pointer to the linked stack data structure.
 * @return The last element that was added to the stack, or NULL if the stack
 * was empty.
 */
void *ls_pop(LStack *ls);

/**
 * Returns the last element that was added to the linked stack.
 *
 * @param ls Pointer to the linked stack data structure.
 * @return The last element that was added to the linked stack, or NULL if the
 * stack was empty.
 */
void *ls_peek(LStack *ls);

/**
 * Traverse all the items of the linked stack and call a function for each of
 * them.
 *
 * @param ls Pointer to the linked stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ls_foreach(LStack *ls, ITERATOR_FUNC iterator_func, void *data);

#endif // _L_STACK_H
