#include "bitset.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <bitset.h>

/** The number of bits for the base storage. */
#define BITS_PER_WORD (sizeof(BS_WORD) * CHAR_BIT)

/** The number of words needed to represent the number of bits. */
#define WORDS_FOR_BITS(n) ((n) / BITS_PER_WORD + ((n) % BITS_PER_WORD == 0 ? 0 : 1))

bool bs_init(BitSet *bs, size_t n) {
    // Make sure that the requested size is greater than zero
    if (n == 0) {
        return false;
    }

    // Initialize the storage
    bs->bits = malloc(WORDS_FOR_BITS(n) * sizeof(BS_WORD));
    if (!bs->bits) {
        return false;
    }
    memset(bs->bits, 0, WORDS_FOR_BITS(n) * sizeof(BS_WORD));
    bs->n = n;

    return true;
}

void bs_destroy(BitSet *bs) {
    free(bs->bits);
}

bool bs_set(BitSet *bs, size_t n) {
    if (n > bs->n) {
        return false;
    }

    bs->bits[n / BITS_PER_WORD] |= 1u << n % BITS_PER_WORD;

    return true;
}

bool bs_clear(BitSet *bs, size_t n) {
    if (n > bs->n) {
        return false;
    }

    bs->bits[n / BITS_PER_WORD] &= ~(1u << n % BITS_PER_WORD);

    return true;
}

bool bs_is_set(BitSet *bs, size_t n) {
    if (n > bs->n) {
        return false;
    }

    return (bool) (bs->bits[n / BITS_PER_WORD] & (1u << n % BITS_PER_WORD));
}

void bs_print(BitSet *bs, FILE *f) {
    for (size_t i = WORDS_FOR_BITS(bs->n); i-- > 0; ) {
        for (size_t j = BITS_PER_WORD; j-- > 0; ) {
            fputs((bs->bits[i] >> j) & 1u ? "1" : "0", f);
        }
    }
}