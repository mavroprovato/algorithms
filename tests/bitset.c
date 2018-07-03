#include "bitset.h"

#include <stdlib.h>

int main(void) {
    size_t size = 40;
    BitSet bs;
    bs_init(&bs, size);
    for (size_t i = 0; i < size; i++) {
        bs_set(&bs, i);
        bs_print(&bs, stdout);
        puts("");
    }
    bs_destroy(&bs);

    return EXIT_SUCCESS;
}
