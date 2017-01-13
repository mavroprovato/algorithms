
#include "linked_stack.h"

/**
 * Initialize the stack data structure.
 *
 * @param ls Pointer to the stack data structure.
 * @return true if the data structure was initialized successfully, false
 * otherwise.
 */
bool ls_init(LinkedStack *ls) {
    ls->ll = NULL;
    ls->size = 0;

    return true;
}

/**
 * Frees resources associated with the stack data structure.
 *
 * @param ls Pointer to the stack data structure to be freed.
 */
void ls_destroy(LinkedStack *ls) {
    ll_destroy(ls->ll);
}

/**
 * Check if the stack contains any elements.
 *
 * @param ls Pointer to the stack data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool ls_is_empty(LinkedStack *ls) {
    return ll_is_empty(ls->ll);
}

/**
 * Return the size of the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The size of the stack.
 */
size_t ls_size(LinkedStack *ls) {
    return ls->size;
}

/**
 * Add an element to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @param item Pointer to the item to add to the stack.
 */
bool ls_push(LinkedStack *ls, void *item) {
    bool success = ll_prepend(&ls->ll, item);
    if (success) {
        ls->size++;
    }

    return success;
}

/**
 * Removes and returns the last element that was added to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *ls_pop(LinkedStack *ls) {
    void *item = ll_remove_first(&ls->ll);
    if (item) {
        ls->size--;
    }

    return item;
}

/**
 * Returns the last element that was added to the stack.
 *
 * @param ls Pointer to the stack data structure.
 * @return The last element that was added to the stack.
 */
void *ls_peek(LinkedStack *ls) {
    return ls->ll ? ls->ll->item : NULL;
}

/**
 * Traverse all the items of the stack and call a function for each of them.
 *
 * @param ls Pointer to the stack data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
void ls_foreach(LinkedStack *ls, ITERATOR_FUNC iterator_func, void *data) {
    ll_foreach(ls->ll, iterator_func, data);
}
