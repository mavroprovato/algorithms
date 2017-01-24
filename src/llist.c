#include "llist.h"

#include <stdlib.h>

bool ll_init(LList *ll) {
    // Initialize the structure fields
    ll->head = NULL;

    return true;
}

void ll_destroy(LList *ll) {
    // Loop through all elements and free the nodes.
    LListNode *current = ll->head;
    while (current) {
        LListNode *node = current;
        current = current->next;
        free(node);
    }

    // Set pointer to NULL
    ll->head = NULL;
}

size_t ll_size(LList *ll) {
    // Loop through all the elements to get the size
    size_t size = 0;
    LListNode *current = ll->head;
    while (current) {
        size++;
        current = current->next;
    }

    return size;
}

bool ll_is_empty(LList *ll) {
    return ll->head == NULL;
}

bool ll_prepend(LList *ll, void *item) {
    // Create the node
    LListNode *node = malloc(sizeof(LListNode *));
    if (!node) {
        return false;
    }
    node->item = item;

    // Put it at the start of the list
    node->next = ll->head;
    ll->head = node;

    return true;
}

bool ll_append(LList *ll, void *item) {
    // Create the node
    LListNode *node = malloc(sizeof(LListNode *));
    if (!node) {
        return false;
    }
    node->item = item;
    node->next = NULL;

    if (ll->head) {
        // Find the last node
        LListNode *current = ll->head;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    } else {
        // List is empty
        ll->head = node;
    }

    return true;
}

bool ll_insert(LList *ll, void *item, size_t position) {
    // If empty or position is zero, call prepend.
    if (!ll->head || position == 0) {
        return ll_prepend(ll, item);
    }

    // Alocate the node
    LListNode *node = malloc(sizeof(LListNode *));
    if (!node) {
        return false;
    }
    node->item = item;

    // Find the node before the requested position
    LListNode *current = ll->head;
    size_t index = 0;
    while (current->next && index++ < position - 1) {
        current = current->next;
    }

    // Insert the node
    node->next = current->next;
    current->next = node;

    return true;
}

void *ll_remove_first(LList *ll) {
    // If list is empty return NULL.
    if (!ll->head) {
        return NULL;
    }

    // Point the node to the next item and free resources.
    void *item = ll->head->item;
    LListNode *node = ll->head;
    ll->head = ll->head->next;
    free(node);

    return item;
}

void *ll_remove_last(LList *ll) {
    // If list is empty return NULL.
    if (!ll->head) {
        return NULL;
    }

    // Find the node before the last one
    LListNode *current = ll->head;
    while (current->next && current->next->next) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) {
        // Only one item in the list
        item = current->item;
        ll->head = NULL;
        free(current);
    } else {
        item = current->next->item;
        free(current->next);
        current->next = NULL;
    }

    return item;
}

void *ll_remove(LList *ll, size_t position) {
    // If list is empty or position is zero, remove the first.
    if (!ll->head || position == 0) {
        return ll_remove_first(ll);
    }

    // Find the node previous to the one we want to remove
    LListNode *current = ll->head;
    size_t index = 0;
    while (current->next && current->next->next && index++ < position - 1) {
        current = current->next;
    }
    void *item = NULL;
    if (current->next == NULL) {
        // The last element of the list
        item = current->item;
        ll->head = NULL;
        free(current);
    } else {
        LListNode *node = current->next;
        item = node->item;
        current->next = current->next->next;
        free(node);
    }

    return item;
}

void *ll_remove_item(LList *ll, void *item, COMPARE_FUNC compare_func) {
    if (!ll->head) { // Empty list
        return NULL;
    }

    // Search for the item
    LListNode *current = ll->head;
    LListNode *previous = NULL;
    while (current && compare_func(current->item, item) != 0) {
        previous = current;
        current = current->next;
    }

    void *found_item = NULL;
    if (current) { // Found
        found_item = current->item;
        if (previous) {
            previous->next = current->next;
        } else {
            // The list only had one element
            ll->head = NULL;
        }
        free(current);
    }

    // Not found
    return found_item;
}

void ll_foreach(LList *ll, ITERATOR_FUNC iterator_func, void *data) {
    // Loop through all the elements and call the function
    LListNode *current = ll->head;
    while (current) {
        iterator_func(current->item, data);
        current = current->next;
    }
}

bool ll_contains(LList *ll, void *item, COMPARE_FUNC compare_func) {
    return ll_find(ll, item, compare_func) != NULL;
}

LListNode *ll_find(LList *ll, void *item, COMPARE_FUNC compare_func) {
    LListNode *current = ll->head;
    while (current && compare_func(current->item, item) != 0) {
        current = current->next;
    }

    return current;
}

void ll_reverse(LList *ll) {
    if (!ll->head || !ll->head->next) {
        // Less than two elements, no need to do anything
        return;
    }

    LListNode *previous = NULL;
    LListNode *current = ll->head;
    LListNode *next = current->next;

    while (current) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    ll->head = previous;
}
