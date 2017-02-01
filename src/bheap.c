
#include "bheap.h"

#include <stdlib.h>

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
