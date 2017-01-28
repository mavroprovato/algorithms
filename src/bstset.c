#include <stddef.h>
#include <stdlib.h>

#include "bstset.h"

bool bs_init(BSTSet *bs, COMPARE_FUNC compare_func) {
    bs->root = NULL;
    bs->compare_func = compare_func;

    return true;
}

bool bs_add(BSTSet *bs, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }
    BSTNode *node = bs->root;
    while (node) {
        int cmp = bs->compare_func(node->item, item);
        if (cmp < 0) {
            node = node->left;
        } else if (cmp > 0) {
            node = node->right;
        } else {
            // The set already contains the element
            return true;
        }
    }

    // Allocate the node
    node = malloc(sizeof(BSTNode));
    if (!node) {
        return false;
    }
    node->item = item;
    node->left = NULL;
    node->right = NULL;

    return true;
}

bool as_is_empty(BSTSet *bs) {
    return bs->root == NULL;
}

bool bs_contains(BSTSet *bs, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }
    BSTNode *node = bs->root;
    while (node) {
        int cmp = bs->compare_func(node->item, item);
        if (cmp < 0) {
            node = node->left;
        } else if (cmp > 0) {
            node = node->right;
        } else {
            // The set contains the element
            return true;
        }
    }

    // Not found
    return false;
}
