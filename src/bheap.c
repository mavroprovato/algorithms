
#include "bheap.h"

#include <stdlib.h>
#include <string.h>

#define PARENT(x) (((x) - 1) / 2)
#define LEFT_CHILD(x) ((2 * (x)) + 1)
#define RIGHT_CHILD(x) ((2 * (x)) + 2)

/**
 * Resize the underlying array holding the heap items.
 *
 * @param bh Pointer to the binary heap data structure.
 * @param new_capacity The new capacity.
 * @return true if the resizing was successful, false otherwise.
 */
static bool bh_resize(BHeap *bh, size_t new_capacity) {
    // Allocate the new array
    void *new_items = malloc(new_capacity * sizeof(void *));
    if (!new_items) {
        return false;
    }

    // Copy the items to the new array.
    memcpy(new_items, bh->items, bh->size * sizeof(void *));

    free(bh->items);
    bh->items = new_items;
    bh->capacity = new_capacity;

    return true;
}


static void bh_swim_up(BHeap *bh, size_t pos) {
    // Check if the item is smaller than its parent
    while (pos != 0 && bh->compare_func(bh->items[pos], bh->items[PARENT(pos)]) < 0) {
        // It is smaller, so swap them
        void *temp = bh->items[pos];
        bh->items[pos] = bh->items[PARENT(pos)];
        bh->items[PARENT(pos)] = temp;

        // Check the new parent of the item
        pos = PARENT(pos);
    }
}

static void bh_sink_down(BHeap *bh, size_t pos) {
    while (LEFT_CHILD(pos) < bh->size) {
        // Find the smallest child
        size_t smallest = LEFT_CHILD(pos);
        if (RIGHT_CHILD(pos) < bh->size &&
            bh->compare_func(bh->items[RIGHT_CHILD(pos)], bh->items[smallest]) < 0) {
            smallest = RIGHT_CHILD(pos);
        }
        // Check if the item is bigger than the smallest child
        if (bh->compare_func(bh->items[pos], bh->items[smallest]) <= 0) {
            // It is not, so the heap invariant holds
            return;
        }
        // It is bigger, so swap them
        void *temp = bh->items[pos];
        bh->items[pos] = bh->items[smallest];
        bh->items[smallest] = temp;

        // Check the new child
        pos = smallest;
    }
}

static bool bh_is_heap(BHeap *bh, size_t pos) {
    if (pos >= bh->size) {
        return true;
    }

    // Check if item is smaller than its children
    if (LEFT_CHILD(pos) < bh->size &&
        bh->compare_func(bh->items[pos], bh->items[LEFT_CHILD(pos)]) > 0) {
        return false;
    }
    if (RIGHT_CHILD(pos) < bh->size &&
        bh->compare_func(bh->items[pos], bh->items[RIGHT_CHILD(pos)]) > 0) {
        return false;
    }

    // Recursively check the subtrees
    return bh_is_heap(bh, LEFT_CHILD(pos)) && bh_is_heap(bh, RIGHT_CHILD(pos));
}

bool bh_init(BHeap *bh, COMPARE_FUNC compare_func) {
    bh->capacity = 1;
    bh->items = malloc(bh->capacity * sizeof(void *));
    if (!bh->items) {
        return false;
    }
    bh->size = 0;
    bh->compare_func = compare_func;

    return true;
}

void bh_destroy(BHeap *bh) {
    free(bh->items);
}

bool bh_is_empty(BHeap *bh) {
    return bh->size == 0;
}

size_t bh_size(BHeap *bh) {
    return bh->size;
}

bool bh_insert(BHeap *bh, void *item) {
    if (!item) {
        // NULL items cannot be added to the heap
        return false;
    }
    if (bh->size == bh->capacity && !bh_resize(bh, 2 * bh->capacity)) {
        // Could not resize the underlying array
        return false;
    }

    // Set the item and move it to the correct position.
    bh->items[bh->size] = item;
    bh_swim_up(bh, bh->size);
    bh->size++;

    // Check the heap invariant
    bh_is_heap(bh, 0);

    return true;
}

void *bh_remove_min(BHeap *bh) {
    if (bh->size == 0) {
        // Heap is empty
        return NULL;
    }
    bh->size--;
    void *item = bh->items[0];
    if (bh->size > 0) {
        // Place the element at the root and sink down as needed
        bh->items[0] = bh->items[bh->size];
        bh_sink_down(bh, 0);
        if (bh->size == bh->capacity / 4) {
            // The array needs to be shrinked
            bh_resize(bh, bh->capacity / 2);
        }
    }

    // Check the heap invariant
    bh_is_heap(bh, 0);

    return item;
}

void *bh_peek(BHeap *bh) {
    return bh->size == 0 ? NULL : bh->items[0];
}
