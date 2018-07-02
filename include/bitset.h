#ifndef _BITSET_H
#define _BITSET_H

#include <stddef.h>
#include <stdbool.h>

/**
 * The bit set structure
 */
typedef struct {
    /** The storage. */
    void *bits;
    /** The number of bits that the set holds. */
    size_t n;
} BitSet;

/**
 * Initialize the bit set.
 *
 * @param bs Pointer to the bit set data structure.
 * @param n The number of bits that the set holds.
 * @return true if the data structure was initialized successfully, false otherwise.
 */
bool bs_init(BitSet *bs, size_t n);

/**
 * Free resources associated with the bit set.
 *
 * @param bs Pointer to the bit set data structure to be freed.
 */
void bs_destroy(BitSet *bs);

#endif // _BITSET_H
