#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "bstset.h"

/**
 * Check whether this tree is a valid binary search tree. The invariant is that
 * each node should be greater that all the elements in the left subtree and
 * less than all elements in the right subtree.
 *
 * @param node The start node to check. Should be called with the root node
 * initially.
 * @param min The tree node value should be strictly greater than this value.
 * Initially, this value is NULL and no check if performed.
 * @param max The tree node value should be strictly less than this value.
 * Initially, this value is NULL and no check if performed.
 */
static bool bs_is_bst(BSTSet *bs, BSTNode *node, void *min, void *max) {
    if (!node) {
        return true;
    }
    if (min && bs->compare_func(min, node->item) >= 0) {
        return false;
    }
    if (max && bs->compare_func(max, node->item) <= 0) {
        return false;
    }

    return bs_is_bst(bs, node->left, min, node->item) &&
           bs_is_bst(bs, node->right, node->item, max);
}

/**
 * Recursively free the recourses associated with a node and all of its
 * descendants.
 *
 * @param node The node for which the resources should be released.
 */
static void bs_destroy_node(BSTNode *node) {
    if (!node) {
        // Node is NULL, nothing to do
        return;
    }
    // Free the sub-tree resources recursively
    bs_destroy_node(node->left);
    bs_destroy_node(node->right);

    // Free the node
    free(node->item);
    free(node);
}

/**
 * Recursively find the size of the sub-tree rooted at the specified node.
 *
 * @param node The node for which to get the size.
 * @return The size of the sub-tree rooted at the node.
 */
static size_t bs_size_node(BSTNode *node) {
    if (!node) {
        // Node is NULL, so its size is zero
        return 0;
    }

    return bs_size_node(node->left) + 1 + bs_size_node(node->right);
}

/**
 * Function to iterate a tree node and all of its sub-trees in order and call a
 * function for each of them.
 *
 * @param node The node that specifies the tree to iterate.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse the items in reverse sorted order.
 */
void bs_foreach_node(BSTNode *node, ITERATOR_FUNC iterator_func, void *data,
                     bool reverse) {
    if (!node) {
        return;
    }
    // Perform an in-oder traversal of the tree.
    // Visit the left subtree (or the right if we traversing in reverse)
    bs_foreach_node(reverse ? node->right : node->left, iterator_func, data,
                    reverse);
    // Visit the node
    iterator_func(node->item, data);
    // Visit the right subtree (or the left if we traversing in reverse)
    bs_foreach_node(reverse ? node->left : node->right, iterator_func, data,
                    reverse);
}

bool bs_init(BSTSet *bs, COMPARE_FUNC compare_func) {
    bs->root = NULL;
    bs->compare_func = compare_func;

    return true;
}

void bs_destroy(BSTSet *bs) {
    bs_destroy_node(bs->root);
}

bool bs_is_empty(BSTSet *bs) {
    return bs->root == NULL;
}

size_t bs_size(BSTSet *bs) {
    return bs_size_node(bs->root);
}

bool bs_add(BSTSet *bs, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }

    // Find the correct position to add the node.
    BSTNode **node = &bs->root;
    while (*node) {
        int cmp = bs->compare_func(item, (*node)->item);
        if (cmp < 0) {
            node = &(*node)->left;
        } else if (cmp > 0) {
            node = &(*node)->right;
        } else {
            // The set already contains the element
            return true;
        }
    }

    // Allocate the node
    *node = malloc(sizeof(BSTNode));
    if (!*node) {
        return false;
    }
    (*node)->item = item;
    (*node)->left = NULL;
    (*node)->right = NULL;

    // Check the invariants
    assert(bs_is_bst(bs, bs->root, NULL, NULL));

    return true;
}

bool bs_contains(BSTSet *bs, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }
    BSTNode *node = bs->root;
    while (node) {
        int cmp = bs->compare_func(item, node->item);
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

void *bs_min(BSTSet *bs) {
    BSTNode *node = bs->root;
    if (!node) {
        // The set is emtpy
        return NULL;
    }

    while (node->left) {
        node = node->left;
    }

    return node->item;
}

void *bs_max(BSTSet *bs) {
    BSTNode *node = bs->root;
    if (!node) {
        // The set is emtpy
        return NULL;
    }

    while (node->right) {
        node = node->right;
    }

    return node->item;
}

void bs_foreach(BSTSet *bs, ITERATOR_FUNC iterator_func, void *data,
                bool reverse) {
    bs_foreach_node(bs->root, iterator_func, data, reverse);
}
