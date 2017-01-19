#include "dllist.h"

#include <stdlib.h>

DLList *dll_create(void *item) {
    DLList *dll = malloc(sizeof(DLList));
    if (!dll) {
        return NULL;
    }
    dll->item = item;
    dll->next = NULL;
    dll->previous = NULL;

    return dll;
}

void dll_destroy(DLList *dll) {
    free(dll);
}

size_t dll_size(DLList *dll) {
    size_t size = 0;
    DLList *current = dll;
    while (current) {
        current = current->next;
        size++;
    }

    return size;
}

bool dll_is_empty(DLList *dll) {
    return dll == NULL;
}

bool dll_prepend(DLList **dll, void *item) {
    // Alocate the node
    DLList *node = dll_create(item);
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

bool dll_append(DLList **dll, void *item) {
    // Alocate the node
    DLList *node = dll_create(item);
    if (!node) {
        return false;
    }

    if (!*dll) {
        // List is empty
        *dll = node;
    } else {
        DLList *current = *dll;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
        node->previous = current;
    }

    return true;
}

bool dll_insert(DLList **dll, void *item, size_t position) {
    // If empty or position is zero, call prepend.
    if (!*dll || position == 0) {
        return dll_prepend(dll, item);
    }

    // Alocate the node
    DLList *node = dll_create(item);
    if (!node) {
        return false;
    }

    // Put it at the requested position
    DLList *current = *dll;
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

void *dll_remove_first(DLList **dll) {
    // If list is empty return null.
    if (!*dll) {
        return NULL;
    }

    // Point the node to the next item and free resources.
    void *item = (*dll)->item;
    DLList *node = *dll;
    *dll = (*dll)->next;
    if (*dll) {
        (*dll)->previous = NULL;
    }
    free(node);

    return item;
}

void *dll_remove_last(DLList **dll) {
    // If list is empty return null.
    if (!*dll) {
        return NULL;
    }

    // Find and remove the last node
    DLList *current = *dll;
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

void *dll_remove(DLList **dll, size_t position) {
    // If list is empty or position is zero, remove the first.
    if (!*dll || position == 0) {
        return dll_remove_first(dll);
    }

    // Find and remove the node
    DLList *current = *dll;
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
        DLList *node = current->next;
        item = node->item;
        current->next = node->next;
        if (node->next) {
            node->next->previous = current;
        }
        free(node);
    }

    return item;
}

void *dll_remove_item(DLList **dll, void *item,
                     COMPARE_FUNC compare_func) {
    // Find and remove the node
    DLList *current = *dll;
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

void dll_foreach(DLList *dll, ITERATOR_FUNC iterator_func, void *data,
                bool reverse) {
    DLList *current = dll;
    while (current) {
        iterator_func(current->item, data);
        current = reverse ? current->previous : current->next;
    }
}

bool dll_contains(DLList *dll, void *item, COMPARE_FUNC compare_func) {
    return dll_find(dll, item, compare_func, false) != NULL ||
           dll_find(dll, item, compare_func, true) != NULL;
}

DLList *dll_find(DLList *dll, void *item, COMPARE_FUNC compare_func,
                 bool reverse) {
    DLList *current = dll;
    while (current && compare_func(current->item, item) != 0) {
        current = reverse ? current->previous : current->next;
    }

    return current;
}

void dll_reverse(DLList **dll) {
    if (!*dll || !(*dll)->next) {
        // Less than two elements, no need to do anything
        return;
    }

    DLList *current = *dll;
    DLList *previous = NULL;
    while (current->next) {
        // Swap the pointers
        DLList *temp = current->next;
        current->next = current->previous;
        current->previous = temp;
        previous = current;
        current = temp;
    }

    current->next = previous;
    current->previous = NULL;
    *dll = current;
}
