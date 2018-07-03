#include "bitset.h"

#include <stdlib.h>

int main(void) {
    size_t size = 32;
    BitSet bs;
    bs_init(&bs, size);

    printf("Setting bits\n");
    for (size_t i = 0; i < size; i++) {
        bs_set(&bs, i);
        bs_print(&bs, stdout);
        puts("");
    }

    printf("Clearing bits\n");
    for (size_t i = 0; i < size; i++) {
        bs_clear(&bs, i);
        bs_print(&bs, stdout);
        puts("");
    }

    bs_destroy(&bs);

    return EXIT_SUCCESS;
}
