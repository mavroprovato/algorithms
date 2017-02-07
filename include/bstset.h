#ifndef _BST_SET_H
#define _BST_SET_H

#include <stdbool.h>
#include <stddef.h>

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
    COMPARE_FUNC compare;
} BSTSet;

/**
 * Initialize the binary search tree set.
 *
 * @param bs Pointer to the binary search tree set data structure to initialize.
 * @param compare Function used to compare the items.
 * @return true If the binary search tree set was initialized successfully,
 * false otherwise.
 */
bool bs_init(BSTSet *bs, COMPARE_FUNC compare);

/**
 * Frees resources associated with the binary search tree set data structure.
 *
 * @param bs Pointer to the binary search tree set data structure to be freed.
 */
void bs_destroy(BSTSet *bs);

/**
 * Check if the binary search tree contains any elements.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @return true if the stack contains elements, false otherwise.
 */
bool bs_is_empty(BSTSet *bs);

/**
 * Return the size of the binary search tree.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @return The size of the binary search tree set.
 */
size_t bs_size(BSTSet *bs);

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
 * Remove the minimum item contained in the binary search tree set.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @return The item removed or NULL if the tree was empty.
 */
void *bs_remove_min(BSTSet *bs);

/**
 * Remove the maximum item contained in the binary search tree set.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @return The item removed or NULL if the tree was empty.
 */
void *bs_remove_max(BSTSet *bs);

/**
 * Check if the binary search tree set contains an item.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @param item Pointer to the item.
 * @return true if the binary search tree set contains the item, false
 * otherwise.
 */
bool bs_contains(BSTSet *bs, void *item);

/**
 * Return the minimum item contained in the binary search tree set.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @return The minimum item contained in the binary search tree set, or NULL if
 * the set is empty.
 */
void *bs_min(BSTSet *bs);

/**
 * Return the maximum item contained in the binary search tree set.
 *
 * @param bs Pointer to the binary search tree set data structure.
 * @return The maximum item contained in the binary search tree set, or NULL if
 * the set is empty.
 */
void *bs_max(BSTSet *bs);

/**
 * Traverse all the items of the binary search tree set in sorted order (or in
 * reverse sorted order) and call a function for each of them.
 *
 * @param bs Pointer to the doubly linked list data structure.
 * @param iterator_func Pointer to function that is called for every item.
 * @param data Pointer to the custom user data. Can be NULL.
 * @param reverse Set to true to traverse the items in reverse sorted order.
 */
void bs_foreach(BSTSet *bs, ITERATOR_FUNC iterator_func, void *data,
                bool reverse);

#endif // _BST_SET_H
