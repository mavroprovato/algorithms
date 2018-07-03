#ifndef _BITSET_H
#define _BITSET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/** Defines the base unit of storage used. */
typedef unsigned int BS_WORD;

/**
 * The bit set structure
 */
typedef struct {
    /** The storage. */
    BS_WORD *bits;
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

/**
 * Set a bit at the specified position.
 *
 * @param bs Pointer to the bit set data structure.
 * @param n The position to set.
 * @return true if
 */
bool bs_set(BitSet *bs, size_t n);

/**
 * Print the bit set to a stream.
 *
 * @param bs Pointer to the bit set data structure.
 * @param f The stream.
 */
void bs_print(BitSet *bs, FILE *f);

#endif // _BITSET_H
