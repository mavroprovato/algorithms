
#include <string.h>
#include <stdlib.h>

#include "trieset.h"

static TrieSetNode *ts_create_node(void) {
    TrieSetNode *node = malloc(sizeof(TrieSetNode *));
    if (!node) {
        return NULL;
    }
    memset(node->children, 0, CHAR_MAX * sizeof(TrieSetNode *));

    return node;
}

static void bs_destroy_node(TrieSetNode *node) {
    if (!node) {
        return;
    }
    for (size_t i = 0; i < CHAR_MAX; i++) {
        bs_destroy_node(node->children[i]);
    }
    free(node);
}

bool ts_init(TrieSet *ts) {
    ts->root = ts_create_node();
    if (!ts->root) {
        return false;
    }
    ts->size = 0;

    return true;
}

void ts_destroy(TrieSet *ts) {
    bs_destroy_node(ts->root);
}

bool ts_is_empty(TrieSet *ts) {
    return ts->size == 0;
}

size_t ts_size(TrieSet *ts) {
    return ts->size;
}
