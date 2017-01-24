#include "dllist.h"

#include <stdlib.h>

/**
 * Remove a node from the doubly linked list.
 *
 * @param dll Pointer to the doubly linked list data structure.
 * @param node Pointer to the node to remove.
 * @return The item that was removed, or NULL if the item was not found.
 */
static void *dll_remove_node(DLList *dll, DLListNode *node) {
    void *item = node->item;
    if (node->previous) {
        node->previous->next = node->next;
    } else {
        dll->head = node->next;
    }
    if (node->next) {
        node->next->previous = node->previous;
    } else {
        dll->tail = node->previous;
    }
    free(node);

    return item;
}

bool dll_init(DLList *dll) {
    // Initialize the stucture fields
    dll->head = NULL;
    dll->tail = NULL;

    return true;
}

void dll_destroy(DLList *dll) {
    // Loop through all elements and free the nodes.
    DLListNode *current = dll->head;
    while (current) {
        DLListNode *node = current;
        current = current->next;
        free(node);
    }

    // Set pointer to NULL
    dll->head = NULL;
}

size_t dll_size(DLList *dll) {
    // Loop through all the elements to get the size
    size_t size = 0;
    DLListNode *current = dll->head;
    while (current) {
        size++;
        current = current->next;
    }

    return size;
}

bool dll_is_empty(DLList *dll) {
    return dll->head == NULL;
}

bool dll_prepend(DLList *dll, void *item) {
    // Create the node
    DLListNode *node = malloc(sizeof(DLListNode *));
    if (!node) {
        return false;
    }
    node->item = item;
    node->previous = NULL;

    // Put it at the start of the list
    node->next = dll->head;
    dll->head = node;
    if (!dll->tail) {
        // The list was empty
        dll->tail = node;
    }

    return true;
}

bool dll_append(DLList *dll, void *item) {
    // Create the node
    DLListNode *node = malloc(sizeof(DLListNode *));
    if (!node) {
        return false;
    }
    node->item = item;
    node->next = NULL;

    // Put it at the end of the list
    node->previous = dll->tail;
    dll->tail = node;
    if (!dll->head) {
        // The list was empty
        dll->head = node;
    }

    return true;
}

bool dll_insert(DLList *dll, void *item, size_t position) {
    // If empty or position is zero, call prepend.
    if (!dll->head || position == 0) {
        return dll_prepend(dll, item);
    }

    // Create the node
    DLListNode *node = malloc(sizeof(DLListNode *));
    if (!node) {
        return false;
    }
    node->item = item;

    // Find the node before the requested position
    DLListNode *current = dll->head;
    size_t index = 0;
    while (current->next && index++ < position) {
        current = current->next;
    }

    // Insert the new node
    node->next = current->next;
    node->previous = current;
    if (current->next) {
        current->next->previous = node;
    }
    current->next = node;

    return true;
}

void *dll_remove_first(DLList *dll) {
    if (!dll->head) {
        // The list is emtpy, return NULL
        return NULL;
    }

    // Point the head to the next item and free resources.
    DLListNode *node = dll->head;
    void *item = node->item;
    dll->head = dll->head->next;
    if (dll->head) {
        // The list is not empty
        dll->head->previous = NULL;
    } else {
        // The list is empty
        dll->tail = NULL;
    }
    free(node);

    return item;
}

void *dll_remove_last(DLList *dll) {
    if (!dll->head) {
        // The list is emtpy, return NULL
        return NULL;
    }

    // Point the node to the next item and free resources.
    DLListNode *node = dll->head;
    void *item = node->item;
    dll->tail = dll->tail->previous;
    if (dll->tail) {
        // The list is not empty
        dll->head->next = NULL;
    } else {
        // The list is empty
        dll->head = NULL;
    }
    free(node);

    return item;
}

void *dll_remove(DLList *dll, size_t position) {
    // If list is empty or position is zero, remove the first.
    if (!dll->head || position == 0) {
        return dll_remove_first(dll);
    }

    // Find and remove the node
    DLListNode *current = dll->head;
    size_t index = 0;
    while (current->next && index++ < position) {
        current = current->next;
    }

    return dll_remove_node(dll, current);
}

void *dll_remove_item(DLList *dll, void *item, COMPARE_FUNC compare_func) {
    // Find the node to remove
    DLListNode *current = dll->head;
    while (current && compare_func(item, current->item) != 0) {
        current = current->next;
    }

    if (current) {
        return dll_remove_node(dll, current);
    }

    // Not found
    return NULL;
}

void dll_foreach(DLList *dll, ITERATOR_FUNC iterator_func, void *data,
                bool reverse) {
    // Loop through all the elements and call the function
    DLListNode *current = reverse ? dll->head : dll->tail;
    while (current) {
        iterator_func(current->item, data);
        current = reverse ? current->previous : current->next;
    }
}

bool dll_contains(DLList *dll, void *item, COMPARE_FUNC compare_func) {
    return dll_find(dll, item, compare_func, false) != NULL;
}

DLListNode *dll_find(DLList *dll, void *item, COMPARE_FUNC compare_func,
                 bool reverse) {
    DLListNode *current = reverse ? dll->head : dll->tail;
    while (current && compare_func(current->item, item) != 0) {
        current = reverse ? current->previous : current->next;
    }

    return current;
}

void dll_reverse(DLList *dll) {
    if (!dll->head || !dll->head->next) {
        // Less than two elements, no need to do anything
        return;
    }

    DLListNode *current = dll->head;
    DLListNode *previous = NULL;
    while (current->next) {
        // Swap the pointers
        DLListNode *temp = current->next;
        current->next = current->previous;
        current->previous = temp;
        previous = current;
        current = temp;
    }

    current->next = previous;
    current->previous = NULL;
    dll->tail = dll->head;
    dll->head = current;
}
