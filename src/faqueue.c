#include "faqueue.h"

#include <stdlib.h>
#include <string.h>

bool faq_init(FAQueue *faq, size_t capacity) {
    faq->capacity = capacity;
    faq->items = malloc(faq->capacity * sizeof(void *));
    if (!faq->items) {
        return false;
    }
    faq->size = 0;
    faq->head = 0;
    faq->tail = 0;

    return true;
}

void faq_destroy(FAQueue *faq) {
    free(faq->items);
    faq->items = NULL;
}

bool faq_is_empty(FAQueue *faq) {
    return faq->size == 0;
}

size_t faq_size(FAQueue *faq) {
    return faq->size;
}

bool faq_enqueue(FAQueue *faq, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }
    if (faq->size == faq->capacity) {
        // Overflow
        return false;
    }
    faq->items[faq->tail++] = item;
    if (faq->tail == faq->capacity) {
         // Wrap around
        faq->tail = 0;
    }
    faq->size++;

    return true;
}

void *faq_dequeue(FAQueue *faq) {
    if (faq->size == 0) {
        // The queue is empty
        return NULL;
    }

    void *item = faq->items[faq->head];
    faq->items[faq->head] = NULL;
    faq->size--;
    faq->head++;
    if (faq->head == faq->capacity) {
        // Wrap around
        faq->head = 0;
    }
    return item;
}

void *faq_peek(FAQueue *faq) {
    if (faq->size == 0) {
        // The queue is empty
        return NULL;
    }

    return faq->items[faq->head];
}

void faq_foreach(FAQueue *faq, ITERATOR_FUNC iterator_func, void *data) {
    if (faq->head <= faq->tail) {
        for (size_t i = faq->head; i < faq->tail; i++) {
            iterator_func(faq->items[i], data);
        }
    } else {
        // The array has wrapped around.
        for (size_t i = faq->head; i < faq->capacity; i++) {
            iterator_func(faq->items[i], data);
        }
        for (size_t i = 0; i < faq->tail; i++) {
            iterator_func(faq->items[i], data);
        }
    }
}
