#ifndef _BST_SET_H
#define _BST_SET_H

#include <stdbool.h>

#include "common.h"

/**
 * The binary search tree node.
 */
typedef struct BSTNode {
    /** The node data. */
    void *item;
    /** The left child. */
    struct BSTNode *left;
    /** The right child. */
    struct BSTNode *right;
} BSTNode;

/**
 * Set implementation based on a binary search tree.
 */
typedef struct {
    /** The root node. */
    BSTNode *root;
    /** The compare function. */
    COMPARE_FUNC compare_func;
} BSTSet;

/**
 * Initialize the binary search tree set.
 *
 * @param bs Pointer to the binary search tree set data structure to initialize.
 * @param compare_func Function used to compare the items.
 * @return true If the binary search tree set was initialized successfully,
 * false otherwise.
 */
bool bs_init(BSTSet *bs, COMPARE_FUNC compare_func);

/**
 * Check if the binary search tree contains any elements.
 *
 * @param bs Pointer to the binary search tree data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool as_is_empty(BSTSet *as);

/**
 * Add an item to the binary search tree set. Note that NULL items cannot be
 * added to the set.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @param item Pointer to the item to be added.
 * @return true if the item was added successfully, false otherwise.
 */
bool bs_add(BSTSet *bs, void *item);

/**
 * Check if the binary search tree set contains an item.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @param item Pointer to the item.
 * @return true if the binary search tree set contains the item, false
 * otherwise.
 */
bool bs_contains(BSTSet *bs, void *item);

#endif // _BST_SET_H
