#include <stdio.h>
#include <string.h>

#include "bheap.h"

/**
 * Compares two list elements. The elements should be strings.
 *
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @return A negative value if a appears before b in lexicographical order, zero
 * if a and b are equal or a positive value if a appears after b in
 * lexicographical order.
 */
int compare_str(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

int main(void) {
    BHeap heap;
    if (!bh_init(&heap, compare_str)) {
        fprintf(stderr, "Cannot create heap.\n");
        return 1;
    }

    bh_insert(&heap, (void *) "Z");
    bh_insert(&heap, (void *) "M");
    bh_insert(&heap, (void *) "A");
    bh_insert(&heap, (void *) "E");
    bh_insert(&heap, (void *) "J");

    while (!bh_is_empty(&heap)) {
        printf("%s\n", (char *) bh_remove_min(&heap));
    }

    bh_destroy(&heap);

    return 0;
}
