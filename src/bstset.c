#include <assert.h>
#include <stdlib.h>

#include "bstset.h"

/**
 * Check whether the tree rooted in this sub-nome is a valid binary search tree. The invariant is that each node should
 * be greater that all the elements in the left subtree and less than all elements in the right subtree.
 *
 * @param node The start node to check. Should be called with the root node initially.
 * @param compare The compare function to use
 * @param min The tree node value should be strictly greater than this value. Initially, this value is NULL and no check
 * if performed.
 * @param max The tree node value should be strictly less than this value. Initially, this value is NULL and no check if
 * performed.
 */
static bool bsts_is_bst(BSTNode *node, COMPARE_FUNC compare, void *min, void *max) {
    if (!node) {
        // Node is NULL
        return true;
    }
    if (min && compare(min, node->item) >= 0) {
        // The item is not less than the minimum, so the invariant does not
        // hold.
        return false;
    }
    if (max && compare(max, node->item) <= 0) {
        // The item is less than the minimum, so the invariant does not hold.
        return false;
    }

    // Check if both the left and the right subtrees are binary search trees. The left subtree must be smaller that the
    // current item, and the right subtree must be bigger than the current item for the invariant to hold.
    return bsts_is_bst(node->left, compare, min, node->item) && bsts_is_bst(node->right, compare, node->item, max);
}

/**
 * Recursively free the resources associated with a node and all of its descendants.
 *
 * @param node The node for which the resources should be released.
 */
static void bsts_destroy_node(BSTNode *node) {
    if (!node) {
        // Node is NULL, nothing to do
        return;
    }
    // Free the sub-tree resources recursively
    bsts_destroy_node(node->left);
    bsts_destroy_node(node->right);

    // Free the node
    free(node);
}

/**
 * Recursively find the size of the sub-tree rooted at the specified node.
 *
 * @param node The node for which to get the size.
 * @return The size of the sub-tree rooted at the node.
 */
static size_t bsts_size_node(BSTNode *node) {
    if (!node) {
        // Node is NULL, so its size is zero
        return 0;
    }

    // The total size is the size of the left and right subtrees plus one
    return bsts_size_node(node->left) + 1 + bsts_size_node(node->right);
}

/**
 * Search for a node in the binary search tree.
 *
 * @param node The node from which to start the search.
 * @param compare The compare function to use for the tree elements.
 * @param item The item to search for.
 * @return The tree node that contains the item, or NULL if the item was not found.
 */
static BSTNode *bsts_find_node(BSTNode *node, COMPARE_FUNC compare, void *item) {
    BSTNode *current = node;
    while (current) {
        int cmp = compare(item, current->item);
        if (cmp < 0) {
            // Smaller than the element, search on the left subtree
            current = current->left;
        } else if (cmp > 0) {
            // Bigger than the element, search on the right subtree
            current = current->right;
        } else {
            // Found
            break;
        }
    }

    return current;
}

/**
 * Remove the minimum node from a binary search tree.
 *
 * @param node The node from where to search for the minimum.
 * @return The minimum node, or NULL if the tree is empty.
 */
static BSTNode *bsts_remove_min_node(BSTNode *node) {
    if (!node) {
        return NULL;
    }

    // Find the left-most node, and keep track of its parent
    BSTNode *parent = NULL;
    while (node->left) {
        parent = node;
        node = node->left;
    }

    // Remove the node
    if (parent) {
        parent->left = node->right;
    }

    return node;
}

/**
 * Remove the maximum node from a binary search tree.
 *
 * @param node The node from where to search for the minimum.
 * @return The maximum node, or NULL if the tree is empty.
 */
static BSTNode *bsts_remove_max_node(BSTNode *node) {
    if (!node) {
        return NULL;
    }

    // Find the left-most node, and keep track of its parent
    BSTNode *parent = NULL;
    while (node->right) {
        parent = node;
        node = node->right;
    }

    // Remove the node
    if (parent) {
        parent->right = node->left;
    }

    return node;
}

/**
 * Function to iterate a tree node and all of its sub-trees in order and call a function for each of them.
 *
 * @param node The node that specifies the tree to iterate.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse the items in reverse sorted order.
 */
static void bsts_foreach_node(BSTNode *node, ITERATOR_FUNC iterator_func, void *data, bool reverse) {
    if (!node) {
        // Node is NULL, nothing to do
        return;
    }
    // Perform an in-oder traversal of the tree.
    // Visit the left subtree (or the right if we traversing in reverse)
    bsts_foreach_node(reverse ? node->right : node->left, iterator_func, data, reverse);
    // Visit the node
    iterator_func(node->item, data);
    // Visit the right subtree (or the left if we traversing in reverse)
    bsts_foreach_node(reverse ? node->left : node->right, iterator_func, data, reverse);
}

bool bsts_init(BSTSet *bs, COMPARE_FUNC compare) {
    // Initialize the structure elements
    bs->root = NULL;
    bs->compare = compare;

    return true;
}

void bsts_destroy(BSTSet *bs) {
    // Destroy the nodes recursively
    bsts_destroy_node(bs->root);
}

bool bsts_is_empty(BSTSet *bs) {
    // Tree is empty if the root node is null
    return bs->root == NULL;
}

size_t bsts_size(BSTSet *bs) {
    // Calculate the size recursively from the root.
    return bsts_size_node(bs->root);
}

bool bsts_add(BSTSet *bs, void *item) {
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
    assert(bsts_is_bst(bs->root, bs->compare, NULL, NULL));

    return true;
}

void *bsts_remove_min(BSTSet *bs) {
    BSTNode *node = bsts_remove_min_node(bs->root);
    if (!node) {
        return NULL;
    }

    if (node == bs->root) {
        // The root node must be removed
        bs->root = node->right;
    }

    // Free resources
    void *item = node->item;
    free(node);

    // Check the invariants
    assert(bsts_is_bst(bs->root, bs->compare, NULL, NULL));

    return item;
}

void *bsts_remove_max(BSTSet *bs) {
    BSTNode *node = bsts_remove_max_node(bs->root);
    if (!node) {
        return NULL;
    }

    if (node == bs->root) {
        // The root node must be removed
        bs->root = node->left;
    }

    // Free resources
    void *item = node->item;
    free(node);

    // Check the invariants
    assert(bsts_is_bst(bs->root, bs->compare, NULL, NULL));

    return item;
}

void *bsts_remove(BSTSet *bs, void *item) {
    // Find the node to remove, and keep track of its parent.
    BSTNode *current = bs->root;
    BSTNode *parent = NULL;
    while (current) {
        int cmp = bs->compare(item, current->item);
        if (cmp < 0) {
            // Smaller than the element, search on the left subtree
            parent = current;
            current = current->left;
        } else if (cmp > 0) {
            // Bigger than the element, search on the right subtree
            parent = current;
            current = current->right;
        } else {
            // Found
            break;
        }
    }

    if (!current) {
        // Node to be deleted not found
        return NULL;
    }

    // Find the new child node that will replace the one to be deleted
    BSTNode *new_child = NULL;
    if (current->left == NULL) {
        new_child = current->right;
    } else if (current->right == NULL) {
        new_child = current->left;
    } else {
        new_child = bsts_remove_min_node(current->right);
        new_child->left = current->left;
        if (current->right != new_child) {
            new_child->right = current->right;
        }
    }

    if (parent) {
        // Replace the node
        if (parent->left == current) {
            parent->left = new_child;
        } else {
            parent->right = new_child;
        }
    } else {
        // We are deleting the root node
        bs->root = new_child;
    }

    // Release the resources associated with the node
    void *removed_item = current->item;
    free(current);

    // Check the invariants
    assert(bsts_is_bst(bs->root, bs->compare, NULL, NULL));

    return removed_item;
}

bool bsts_contains(BSTSet *bs, void *item) {
    if (!item) {
        // NULL items cannot be added
        return false;
    }

    // Search for the node
    BSTNode *node = bsts_find_node(bs->root, bs->compare, item);

    // Check if found
    return node != NULL;
}

void *bsts_min(BSTSet *bs) {
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

void *bsts_max(BSTSet *bs) {
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

void bsts_foreach(BSTSet *bs, ITERATOR_FUNC iterator_func, void *data, bool reverse) {
    // Start the iteration from the root node of the tree
    bsts_foreach_node(bs->root, iterator_func, data, reverse);
}
