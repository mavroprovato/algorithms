#include "bitset.h"

#include <stdlib.h>

int main(void) {
    BitSet bs;
    bs_init(&bs, 10);
    bs_destroy(&bs);

    return EXIT_SUCCESS;
}
