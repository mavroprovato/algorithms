#ifndef _BITSET_H
#define _BITSET_H

/**
 * The bit set structure
 */
typedef struct {
    /** The storage */
    void *bits;
    /** The number of bits to allocate storage for */
    size_t n;
} BitSet;



#endif // _BITSET_H
