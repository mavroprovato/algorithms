#include "llist.h"

#include <stdlib.h>

LList *ll_create(void *item) {
    LList *ll = malloc(sizeof(LList));
    if (!ll) {
        return NULL;
    }
    ll->item = item;
    ll->next = NULL;

    return ll;
}

void ll_destroy(LList *ll) {
    free(ll);
}

size_t ll_size(LList *ll) {
    size_t size = 0;
    LList *current = ll;
    while (current) {
        current = current->next;
        size++;
    }

    return size;
}

bool ll_is_empty(LList *ll) {
    return ll == NULL;
}

bool ll_prepend(LList **ll, void *item) {
    // Alocate the node
    LList *node = ll_create(item);
    if (!node) {
        return false;
    }

    // Put it at the start of the list
    node->next = *ll;
    *ll = node;

    return true;
}

bool ll_append(LList **ll, void *item) {
    // Alocate the node
    LList *node = ll_create(item);
    if (!node) {
        return false;
    }

    if (!*ll) {
        // List is empty
        *ll = node;
    } else {
        LList *current = *ll;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }

    return true;
}

bool ll_insert(LList **ll, void *item, size_t position) {
    // If empty or position is zero, call prepend.
    if (!*ll || position == 0) {
        return ll_prepend(ll, item);
    }

    // Alocate the node
    LList *node = ll_create(item);
    if (!node) {
        return false;
    }

    // Put it at the requested position
    LList *current = *ll;
    size_t index = 0;
    while (current->next && index++ < position - 1) {
        current = current->next;
    }
    node->next = current->next;
    current->next = node;

    return true;
}

void *ll_remove_first(LList **ll) {
    // If list is empty return null.
    if (!*ll) {
        return NULL;
    }

    // Point the node to the next item and free resources.
    void *item = (*ll)->item;
    LList *node = *ll;
    *ll = (*ll)->next;
    free(node);

    return item;
}

void *ll_remove_last(LList **ll) {
    // If list is empty return null.
    if (!*ll) {
        return NULL;
    }

    // Find and remove the last node
    LList *current = *ll;
    while (current->next && current->next->next) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) { // Only one item in the list
        item = current->item;
        (*ll) = NULL;
        free(current);
    } else {
        item = current->next->item;
        free(current->next);
        current->next = NULL;
    }

    return item;
}

void *ll_remove(LList **ll, size_t position) {
    // If list is empty or position is zero, remove the first.
    if (!*ll || position == 0) {
        return ll_remove_first(ll);
    }

    // Find and remove the node
    LList *current = *ll;
    size_t index = 0;
    while (current->next && current->next->next && index++ < position - 1) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) { // The last element of the list
        item = current->item;
        (*ll) = NULL;
        free(current);
    } else {
        LList *node = current->next;
        item = node->item;
        current->next = current->next->next;
        free(node);
    }

    return item;
}

void *ll_remove_item(LList **ll, void *item, COMPARE_FUNC compare_func) {
    if (!*ll) { // Empty list
        return NULL;
    }

    // Search for the item
    LList *current = *(ll);
    LList *previous = NULL;
    while (current && compare_func(current->item, item) != 0) {
        previous = current;
        current = current->next;
    }

    if (current) { // Found
        void *found = current->item;
        if (previous) {
            previous->next = current->next;
        } else {
            (*ll) = NULL;
        }
        free(current);

        return found;
    }

    // Not found
    return NULL;
}

void ll_foreach(LList *ll, ITERATOR_FUNC iterator_func, void *data) {
    LList *current = ll;
    while (current) {
        iterator_func(current->item, data);
        current = current->next;
    }
}

bool ll_contains(LList *ll, void *item, COMPARE_FUNC compare_func) {
    return ll_find(ll, item, compare_func) != NULL;
}

LList *ll_find(LList *ll, void *item, COMPARE_FUNC compare_func) {
    LList *current = ll;
    while (current && compare_func(current->item, item) != 0) {
        current = current->next;
    }

    return current;
}

void ll_reverse(LList **ll) {
    if (!*ll || !(*ll)->next) {
        // Less than two elements, no need to do anything
        return;
    }

    LList *previous = NULL;
    LList *current = *ll;
    LList *next = (*ll)->next;

    while (current) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    *ll = previous;
}
