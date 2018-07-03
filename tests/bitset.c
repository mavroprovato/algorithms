#include "bitset.h"

#include <stdlib.h>

int main(void) {
    size_t size = 40;
    BitSet bs;
    bs_init(&bs, size);

    printf("Setting bits\n");
    for (size_t i = 0; i < size; i+= 2) {
        bs_set(&bs, i);
        bs_print(&bs, stdout);
        puts("");
    }

    printf("Checking bits\n");
    for (size_t i = 0; i < size; i++) {
        printf("Bit %lu is%s set\n", i, bs_is_set(&bs, i) ? "" : " not");
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
