#include "bitset.h"

#include <stdlib.h>

int main(void) {
    BitSet bs;
    bs_init(&bs, 40);
    bs_print(&bs, stdout);
    puts("\n");
    bs_destroy(&bs);

    return EXIT_SUCCESS;
}
