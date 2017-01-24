
#include "lqueue.h"

#include <stdlib.h>

bool lq_init(LQueue *lq) {
    lq->head = NULL;
    lq->tail = NULL;
    lq->size = 0;

    return true;
}

void lq_destroy(LQueue *lq) {
    // Loop through all elements and free the nodes.
    LQueueNode *current = lq->head;
    while (current) {
        LQueueNode *node = current;
        current = current->next;
        free(node);
    }

    // Set pointers to NULL
    lq->head = NULL;
    lq->tail = NULL;
}

bool lq_is_empty(LQueue *lq) {
    return lq->head == NULL;
}

size_t lq_size(LQueue *lq) {
    return lq->size;
}

bool lq_enqueue(LQueue *lq, void *item) {
    // Initialize the node
    LQueueNode *node = malloc(sizeof(LQueueNode));
    if (!node) {
        return false;
    }
    node->item = item;
    node->next = NULL;

    // Append the node to the end
    if (lq->tail) {
        // The queue has elements
        lq->tail->next = node;
        lq->tail = node;
    } else {
        // The queue is empty
        lq->head = node;
        lq->tail = node;
    }
    lq->size++;

    return true;
}

void *lq_dequeue(LQueue *lq) {
    LQueueNode *node = lq->head;
    if (node) {
        // The queue is empty
        return NULL;
    }

    // Remove the first node
    void *item = node->item;
    lq->head = node->next;
    if (!lq->head) {
        // Queue is empty
        lq->tail = NULL;
    }
    free(item);
    lq->size--;

    return item;
}

void *lq_peek(LQueue *lq) {
    return lq->head ? lq->head->item : NULL;
}

void lq_foreach(LQueue *lq, ITERATOR_FUNC iterator_func, void *data) {
    LQueueNode *current = lq->head;
    while (current) {
        iterator_func(current->item, data);
        current = current->next;
    }
}
