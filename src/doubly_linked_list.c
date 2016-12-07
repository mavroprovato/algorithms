#include "doubly_linked_list.h"

#include <stdlib.h>

/**
 * Create a doubly linked list structure.
 *
 * @param item Pointer to the item to hold.
 * @return The created doubly linked list structure or NULL if the stuructre
 * could not be created.
 */
DoublyLinkedList *ll_create(void *item) {
    DoublyLinkedList *dll = malloc(sizeof(DoublyLinkedList));
    if (!dll) {
        return NULL;
    }
    dll->item = item;
    dll->next = NULL;

    return dll;
}

/**
 * Destroy the doubly linked list structure.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to hold.
 */
void dll_destroy(DoublyLinkedList *dll) {
    free(dll);
}

/**
 * Return the size of the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return The size of the doubly linked list.
 */
size_t dll_size(DoublyLinkedList *dll) {
    size_t size = 0;
    DoublyLinkedList *current = dll;
    while (current) {
        current = current->next;
        size++;
    }

    return size;
}

/**
 * Check if the doubly linked list is empty.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @return true if the doubly linked list is empty, false otherwise.
 */
bool dll_is_empty(DoublyLinkedList *dll) {
    return dll == NULL;
}
