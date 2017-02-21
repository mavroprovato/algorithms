#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "bstset.h"

/**
 * Check whether this tree is a valid binary search tree. The invariant is that
 * each node should be greater that all the elements in the left subtree and
 * less than all elements in the right subtree.
 *
 * @oaran bs The binary search tree set.
 * @param node The start node to check. Should be called with the root node
 * initially.
 * @param min The tree node value should be strictly greater than this value.
 * Initially, this value is NULL and no check if performed.
 * @param max The tree node value should be strictly less than this value.
 * Initially, this value is NULL and no check if performed.
 */
static bool bs_is_bst(BSTSet *bs, BSTNode *node, void *min, void *max) {
    if (!node) {
        // Node is NULL
        return true;
    }
    if (min && bs->compare(min, node->item) >= 0) {
        // The item is not less than the minimum, so the invariant does not
        // hold.
        return false;
    }
    if (max && bs->compare(max, node->item) <= 0) {
        // The item is less than the minimum, so the invariant does not hold.
        return false;
    }

    // Check if both the left and the right subtrees are binary search trees.
    // The left subtree must be smaller that the current item, and the right
    // subtree must be bigger than the current item for the invariant to hold.
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

    // The total size is the size of the left and right subtrees plus one
    return bs_size_node(node->left) + 1 + bs_size_node(node->right);
}

/**
 * Search for a node in the binary search tree.
 *
 * @oaran bs The binary search tree set.
 * @param node The node from which to start the search.
 * @param item The item to search for.
 * @return The tree node that contains the item, or NULL if the item was not
 * found.
 */
static BSTNode *bs_find_node(BSTSet *bs, BSTNode *node, void *item) {
    BSTNode *current = node;
    while (node) {
        int cmp = bs->compare(item, current->item);
        if (cmp < 0) {
            // Smaller than the element, search on the left subtree
            node = node->left;
        } else if (cmp > 0) {
            // Bigger than the element, search on the right subtree
            node = node->right;
        } else {
            // Found
            break;
        }
    }

    return current;
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
static void bs_foreach_node(BSTNode *node, ITERATOR_FUNC iterator_func,
                            void *data, bool reverse) {
    if (!node) {
        // Node is NULL, nothing to do
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

bool bs_init(BSTSet *bs, COMPARE_FUNC compare) {
    // Initialize the structure elements
    bs->root = NULL;
    bs->compare = compare;

    return true;
}

void bs_destroy(BSTSet *bs) {
    // Destroy the nodes recursively
    bs_destroy_node(bs->root);
}

bool bs_is_empty(BSTSet *bs) {
    // Tree is empty if the root node is null
    return bs->root == NULL;
}

size_t bs_size(BSTSet *bs) {
    // Calculate the size recursively from the root.
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
        int cmp = bs->compare(item, (*node)->item);
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

void *bs_remove_min(BSTSet *bs) {
    if (!bs->root) {
        // The tree was empty
        return NULL;
    }

    // Find the left-most node, and keep track of its parent
    BSTNode *node = bs->root;
    BSTNode *parent = NULL;
    while (node->left) {
        parent = node;
        node = node->left;
    }

    // Remove the node
    if (parent) {
        parent->left = node->right;
    } else {
        // The root node must be removed
        bs->root = node->right;
    }

    // Free resources
    void *item = node->item;
    free(node);

    // Check the invariants
    assert(bs_is_bst(bs, bs->root, NULL, NULL));

    return item;
}

void *bs_remove_max(BSTSet *bs) {
    if (!bs->root) {
        // The tree was empty
        return NULL;
    }

    // Find the right-most node, and keep track of its parent
    BSTNode *node = bs->root;
    BSTNode *parent = NULL;
    while (node->right) {
        parent = node;
        node = node->right;
    }

    // Remove the node
    if (parent) {
        parent->right = node->left;
    } else {
        // The root node must be removed
        bs->root = node->left;
    }

    // Free resources
    void *item = node->item;
    free(node);

    // Check the invariants
    assert(bs_is_bst(bs, bs->root, NULL, NULL));

    return item;
}

bool bs_contains(BSTSet *bs, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }

    // Search for the node
    BSTNode *node = bs_find_node(bs, bs->root, item);

    // Check if found
    return node != NULL;
}

void *bs_min(BSTSet *bs) {
    BSTNode *node = bs->root;
    if (!node) {
        // The set is empty
        return NULL;
    }

    // The minimum is the left-most node
    while (node->left) {
        node = node->left;
    }

    return node->item;
}

void *bs_max(BSTSet *bs) {
    BSTNode *node = bs->root;
    if (!node) {
        // The set is empty
        return NULL;
    }

    // The minimum is the right-most node
    while (node->right) {
        node = node->right;
    }

    return node->item;
}

void bs_foreach(BSTSet *bs, ITERATOR_FUNC iterator_func, void *data,
                bool reverse) {
    // Start the iteration from the root node of the tree
    bs_foreach_node(bs->root, iterator_func, data, reverse);
}
