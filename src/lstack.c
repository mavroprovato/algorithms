#include "lstack.h"

#include <stdlib.h>

bool ls_init(LStack *ls) {
    ls->head = NULL;
    ls->size = 0;

    return true;
}

void ls_destroy(LStack *ls) {
    // Loop through all elements and free the nodes.
    LStackNode *current = ls->head;
    while (current) {
        LStackNode *node = current;
        current = current->next;
        free(node);
    }

    // Set pointer to NULL
    ls->head = NULL;
}

bool ls_is_empty(LStack *ls) {
    return ls->head == NULL;
}

size_t ls_size(LStack *ls) {
    return ls->size;
}

bool ls_push(LStack *ls, void *item) {
    // Initialize the node
    LStackNode *node = malloc(sizeof(LStackNode));
    if (!node) {
        return false;
    }
    node->item = item;
    node->next = ls->head;

    // Add the node at the start
    ls->head = node;
    ls->size++;

    return true;
}

void *ls_pop(LStack *ls) {
    LStackNode *node = ls->head;
    if (!node) {
        // The stack is empty
        return NULL;
    }

    // Remove the first node
    void *item = node->item;
    ls->head = node->next;
    ls->size--;
    free(node);

    return item;
}

void *ls_peek(LStack *ls) {
    return ls->head ? ls->head->item : NULL;
}

void ls_foreach(LStack *ls, ITERATOR_FUNC iterator_func, void *data) {
    LStackNode *current = ls->head;
    while (current) {
        iterator_func(current->item, data);
        current = current->next;
    }
}
