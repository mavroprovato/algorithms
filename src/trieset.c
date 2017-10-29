#include <string.h>
#include <stdlib.h>

#include "trieset.h"

static TrieSetNode *ts_create_node(void) {
    TrieSetNode *node = malloc(sizeof(TrieSetNode));
    if (!node) {
        return NULL;
    }
    node->children = malloc(UCHAR_MAX * sizeof(TrieSetNode *));
    if (!node->children) {
        free(node);
        return NULL;
    }
    memset(node->children, 0, UCHAR_MAX * sizeof(TrieSetNode *));
    node->leaf = false;

    return node;
}

static void bs_destroy_node(TrieSetNode *node) {
    if (!node) {
        return;
    }
    for (size_t i = 0; i < UCHAR_MAX; i++) {
        bs_destroy_node(node->children[i]);
    }
    free(node->children);
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

bool ts_add(TrieSet *ts, const char *item) {
    if (!item) {
        // NULL strings are not allowed
        return false;
    }
    TrieSetNode *current = ts->root;
    // Loop through all characters of the string
    const char *c = item;
    while (*c) {
        size_t index = *c - CHAR_MIN;
        if (!current->children[index]) {
            // Child node is null, create it
            current->children[index] = ts_create_node();
            if (!current->children[index]) {
                // Could not create node
                return false;
            }
        }
        current = current->children[index];
        c++;
    }
    // The final node is a leaf node
    current->leaf = true;

    ts->size++;

    return true;
}

bool ts_contains(TrieSet *ts, const char *item) {
    if (!item) {
        // NULL strings are not allowed
        return false;
    }
    TrieSetNode *current = ts->root;
    const char *c = item;
    while (*c) {
        size_t index = *c - CHAR_MIN;
        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
        c++;
    }

    return current->leaf;
}
