#include "bitset.h"

#include <stdlib.h>
#include <string.h>

/** Defines the base unit of storage used. */
typedef unsigned int BS_WORD;

bool bs_init(BitSet *bs, size_t n) {
    // Make sure that the requested size is greater than zero
    if (n == 0) {
        return false;
    }

    // Calculate the number of words we must allocate
    size_t size = (n / (sizeof(BS_WORD) * 8)) + 1;
    if ((n % (sizeof(BS_WORD) * 8)) == 0) {
        size--;
    }

    // Allocate the storage
    bs->bits = malloc(size * sizeof(BS_WORD));
    if (!bs->bits) {
        return false;
    }
    memset(bs->bits, 0, size * 8);
    bs->n = n;

    return true;
}

void bs_destroy(BitSet *bs) {
    free(bs->bits);
}