#ifndef _DOUBLY_LINKED_LIST_H
#define _DOUBLY_LINKED_LIST_H

#include "util.h"

#include <sys/types.h>

#include <stdbool.h>
#include <stddef.h>

/**
 * The doubly linked list structure.
 */
typedef struct DoublyLinkedList {
    /** The item. */
    void *item;
    /** The next node. */
    struct DoublyLinkedList *next;
    /** The previous node. */
    struct DoublyLinkedList *previous;
} DoublyLinkedList;

/**
 * Create a doubly linked list structure.
 *
 * @param item Pointer to the item to hold.
 * @return The created doubly linked list structure or NULL if the stuructre
 * could not be created.
 */
DoublyLinkedList *dll_create(void *item);

/**
 * Destroy the doubly linked list structure.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to hold.
 */
void dll_destroy(DoublyLinkedList *dll);

/**
 * Return the size of the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return The size of the doubly linked list.
 */
size_t dll_size(DoublyLinkedList *dll);

/**
 * Check if the doubly linked list is empty.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return true if the doubly linked list is empty, false otherwise.
 */
bool dll_is_empty(DoublyLinkedList *dll);

/**
 * Add an item as the first element of the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return Pointer to the updated list or NULL if the list cannot be updated.
 */
bool dll_prepend(DoublyLinkedList **dll, void *item);

/**
 * Add an item as the last element of the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_append(DoublyLinkedList **dll, void *item);

/**
 * Insert an item at the specified position of the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_insert(DoublyLinkedList **dll, void *item, size_t position);

/**
 * Remove the first item of the list.
 *
 * @param ll The doubly linked list data structure.
 * @return The item that was removed.
 */
void *dll_remove_first(DoublyLinkedList **dll);

/**
 * Remove the last item of the list.
 *
 * @param ll The doubly linked list data structure.
 * @return The item that was removed.
 */
void *dll_remove_last(DoublyLinkedList **dll);

/**
 * Remove an item from the list by position.
 *
 * @param dll The doubly linked list data structure.
 * @param position The position at which the element is to be inserted.
 * @return The item that was removed.
 */
void *dll_remove(DoublyLinkedList **dll, size_t position);

/**
 * Remove an item from the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item The position at which the element is to be inserted.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove_item(DoublyLinkedList **dll, void *item,
                     COMPARE_FUNC compare_func);

/**
 * Add an item as the last element of the list.
 *
 * @param ll Pointer to the doubly linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse in reverse.
 */
void dll_foreach(DoublyLinkedList *dll, ITERATOR_FUNC iterator_func, void *data,
                bool reverse);

/**
 * Check if the linked list contains an element.
 *
 * @param ll Pointer to the doubly linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
bool dll_contains(DoublyLinkedList *ll, void *item, COMPARE_FUNC compare_func);

/**
 * Search for an element and return its index in the list.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @param reverse Set to true to search in reverse.
 * @return The list node, or NULL if the node was not found.
 */
DoublyLinkedList *dll_find(DoublyLinkedList *ll, void *item,
                           COMPARE_FUNC compare_func, bool reverse);

/**
 * Reverse the doubly linked list.
 *
 * @param ll The doubly linked list data structure.
 */
void dll_reverse(DoublyLinkedList **dll);

#endif // _DOUBLY_LINKED_LIST_H
