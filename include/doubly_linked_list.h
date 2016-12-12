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

#endif // _DOUBLY_LINKED_LIST_H
