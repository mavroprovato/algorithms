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
    dll->previous = NULL;

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
    if (*dll) {
        (*dll)->previous = node;
    }
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
    if (*dll) {
        (*dll)->previous = NULL;
    }
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
    void *item = current->item;
    if (current->previous) {
        // Point the previous node to NULL
        current->previous->next = NULL;
    } else {
        // Only one item
        *dll = NULL;
    }
    free(current);

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
    while (current->next && current->next->next && index++ < position - 1) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) { // The last element of the list
        item = current->item;
        (*dll) = NULL;
        free(current);
    } else {
        DoublyLinkedList *node = current->next;
        item = node->item;
        current->next = node->next;
        if (node->next) {
            node->next->previous = current;
        }
        free(node);
    }

    return item;
}

/**
 * Remove an item from the list.
 *
 * @param dll The doubly linked list data structure.
 * @param item The position at which the element is to be inserted.
 * @return The item that was removed, or NULL if the item was not found.
 */
void *dll_remove_item(DoublyLinkedList **dll, void *item,
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

/**
 * Traverse all the items of the list and call a function for each of them.
 *
 * @param ll Pointer to the linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse in reverse.
 */
void dll_foreach(DoublyLinkedList *dll, ITERATOR_FUNC iterator_func, void *data,
                bool reverse) {
    DoublyLinkedList *current = dll;
    while (current) {
        iterator_func(current->item, data);
        current = reverse ? current->previous : current->next;
    }
}

/**
 * Check if the linked list contains an element.
 *
 * @param ll Pointer to the linked list data structure.
 * @param item The item to search for.
 * @param compare_func The function used to compare items.
 * @return The index of the item, or -1 if the item is not found.
 */
bool dll_contains(DoublyLinkedList *ll, void *item, COMPARE_FUNC compare_func) {
    return dll_find(ll, item, compare_func, false) != NULL ||
           dll_find(ll, item, compare_func, true) != NULL;
}

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
                           COMPARE_FUNC compare_func, bool reverse) {
    DoublyLinkedList *current = ll;
    while (current && compare_func(current->item, item) != 0) {
        current = reverse ? current->previous : current->next;
    }

    return current;
}

/**
 * Reverse the doubly linked list.
 *
 * @param dll The doubly linked list data structure.
 */
void dll_reverse(DoublyLinkedList **dll) {
    if (!*dll || !(*dll)->next) {
        // Less than two elements, no need to do anything
        return;
    }

    DoublyLinkedList *current = *dll;
    DoublyLinkedList *previous = NULL;
    while (current->next) {
        // Swap the pointers
        DoublyLinkedList *temp = current->next;
        current->next = current->previous;
        current->previous = temp;
        previous = current;
        current = temp;
    }

    current->next = previous;
    current->previous = NULL;
    *dll = current;
}
