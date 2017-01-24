#ifndef _DL_LIST_H
#define _DL_LIST_H

#include "util.h"

#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

/**
 * The doubly linked list node.
 */
typedef struct DLListNode {
    /** The item. */
    void *item;
    /** The next node. */
    struct DLListNode *next;
    /** The previous node. */
    struct DLListNode *previous;
} DLListNode;

/**
 * The doubly linked list structure.
 */
typedef struct DLList {
    /** The head node. */
    struct DLListNode *head;
    /** The tail node. */
    struct DLListNode *tail;
} DLList;

/**
 * Initialize the doubly linked list structure.
 *
 * @param ll Pointer to the linked list to initialize.
 * @return true if the linked list was initialized successfully, false
 * otherwise.
 */
bool dll_init(DLList *dll);

/**
 * Destroy the linked list structure.
 *
 * @param dll Pointer to the linked list data structure.
 */
void dll_destroy(DLList *dll);

/**
 * Return the size of the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return The size of the doubly linked list.
 */
size_t dll_size(DLList *dll);

/**
 * Check if the doubly linked list is empty.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return true if the doubly linked list is empty, false otherwise.
 */
bool dll_is_empty(DLList *dll);

/**
 * Add an item as the first element of the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_prepend(DLList *dll, void *item);

/**
 * Add an item as the last element of the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_append(DLList *dll, void *item);

/**
 * Insert an item at the specified position of the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_insert(DLList *dll, void *item, size_t position);

/**
 * Remove the first item of the list.
 *
 * @param ll The doubly linked list data structure.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove_first(DLList *dll);

/**
 * Remove the last item of the list.
 *
 * @param ll The doubly linked list data structure.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove_last(DLList *dll);

/**
 * Remove an item from the list by position.
 *
 * @param dll The doubly linked list data structure.
 * @param position The position of the element to be removed.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove(DLList *dll, size_t position);

/**
 * Remove an item from the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item The position at which the element is to be inserted.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove_item(DLList *dll, void *item, COMPARE_FUNC compare_func);

/**
 * Add an item as the last element of the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse in reverse.
 */
void dll_foreach(DLList *dll, ITERATOR_FUNC iterator_func, void *data,
                bool reverse);

/**
 * Check if the linked list contains an element.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
bool dll_contains(DLList *dll, void *item, COMPARE_FUNC compare_func);

/**
 * Search for an element and return its index in the list.
 *
 * @param dll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @param reverse Set to true to search in reverse.
 * @return The list node, or NULL if the node was not found.
 */
DLListNode *dll_find(DLList *dll, void *item, COMPARE_FUNC compare_func,
                     bool reverse);

/**
 * Reverse the doubly linked list.
 *
 * @param ll The doubly linked list data structure.
 */
void dll_reverse(DLList *dll);

#endif // _DL_LIST_H
