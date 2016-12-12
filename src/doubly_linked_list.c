#include "doubly_linked_list.h"

#include <stdlib.h>

/**
 * Create a doubly linked list structure.
 *
 * @param item Pointer to the item to hold.
 * @return The created doubly linked list structure or NULL if the stuructre
 * could not be created.
 */
DoublyLinkedList *dll_create(void *item) {
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

/**
 * Add an item as the first element of the list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return Pointer to the updated list or NULL if the list cannot be updated.
 */
bool dll_prepend(DoublyLinkedList **dll, void *item) {
    // Alocate the node
    DoublyLinkedList *node = dll_create(item);
    if (!node) {
        return false;
    }

    // Put it at the start of the list
    node->next = *dll;
    (*dll)->previous = node;
    *dll = node;

    return true;
}

/**
 * Add an item as the last element of the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_append(DoublyLinkedList **dll, void *item) {
    // Alocate the node
    DoublyLinkedList *node = dll_create(item);
    if (!node) {
        return false;
    }

    if (!*dll) {
        // List is empty
        *dll = node;
    } else {
        DoublyLinkedList *current = *dll;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
        node->previous = current;
    }

    return true;
}

/**
 * Insert an item at the specified position of the list.
 *
 * @param ll The doubly linked list data structure.
 * @param item Pointer to the item to add.
 * @param position The position at which the element is to be inserted.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dll_insert(DoublyLinkedList **dll, void *item, size_t position) {
    // If empty or position is zero, call prepend.
    if (!*dll || position == 0) {
        return dll_prepend(dll, item);
    }

    // Alocate the node
    DoublyLinkedList *node = dll_create(item);
    if (!node) {
        return false;
    }

    // Put it at the requested position
    DoublyLinkedList *current = *dll;
    size_t index = 0;
    while (current->next && index++ < position - 1) {
        current = current->next;
    }
    node->next = current->next;
    node->previous = current;
    if (current->next) {
        current->next->previous = node;
    }
    current->next = node;

    return true;
}

/**
 * Remove the first item of the list.
 *
 * @param ll The doubly linked list data structure.
 * @return The item that was removed.
 */
void *dll_remove_first(DoublyLinkedList **dll) {
    // If list is empty return null.
    if (!*dll) {
        return NULL;
    }

    // Point the node to the next item and free resources.
    void *item = (*dll)->item;
    DoublyLinkedList *node = *dll;
    *dll = (*dll)->next;
    (*dll)->previous = NULL;
    free(node);

    return item;
}

/**
 * Remove the last item of the list.
 *
 * @param ll The linked list data structure.
 * @return The item that was removed.
 */
void *dll_remove_last(DoublyLinkedList **dll) {
    // If list is empty return null.
    if (!*dll) {
        return NULL;
    }

    // Find and remove the last node
    DoublyLinkedList *current = *dll;
    while (current->next) {
        current = current->next;
    }
    // Point the node to the next item and free resources.
    void *item = (*dll)->item;
    DoublyLinkedList *node = *dll;
    (*dll)->previous->next = NULL;
    free(node);

    return item;
}

/**
 * Remove an item from the list by position.
 *
 * @param dll The doubly linked list data structure.
 * @param position The position at which the element is to be inserted.
 * @return The item that was removed.
 */
void *dll_remove(DoublyLinkedList **dll, size_t position) {
    // If list is empty or position is zero, remove the first.
    if (!*dll || position == 0) {
        return dll_remove_first(dll);
    }

    // Find and remove the node
    DoublyLinkedList *current = *dll;
    size_t index = 0;
    while (current && index++ < position) {
        current = current->next;
    }

    // Delete node and fix links
    void *item = NULL;
    if (current->previous) {
        current->previous->next = current->next;
    }
    if (current->next) {
        current->next->previous = current->previous;
    }
    free(current);

    return item;
}

/**
 * Remove an item from the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item The position at which the element is to be inserted.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *ll_remove_item(DoublyLinkedList **dll, void *item,
                     COMPARE_FUNC compare_func) {
    // Find and remove the node
    DoublyLinkedList *current = *dll;
    while (current && compare_func(item, current->item) != 0) {
        current = current->next;
    }

    if (current) {
        // Item found
        void *found = NULL;
        if (current->previous) {
            current->previous->next = current->next;
        }
        if (current->next) {
            current->next->previous = current->previous;
        }
        free(current);

        return found;
    }

    // Not found
    return NULL;
}
