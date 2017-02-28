#ifndef _TRIE_SET
#define _TRIE_SET

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * The trie tree node.
 */
typedef struct TrieSetNode {
    /** The child nodes. */
    struct TrieSetNode *children[CHAR_MAX];
    /** True if this is a leaf node. */
    bool leaf;
} TrieSetNode;

/**
 * A trie based set implementation.
 */
typedef struct {
    /** The root node. */
    TrieSetNode *root;
    /** The set size. */
    size_t size;
} TrieSet;


/**
 * Initialize the trie set data structure.
 *
 * @param ts Pointer to the trie set data structure to initialize.
 * @return true If the trie set data structure was initialized successfully,
 * false otherwise.
 */
bool ts_init(TrieSet *ts);

/**
 * Release the resources associated with the trie set data structure.
 *
 * @param ts Pointer to the trie set data structure to be freed.
 */
void ts_destroy(TrieSet *ts);

/**
 * Check if the trie set contains any elements.
 *
 * @param ts Pointer to the trie set data structure.
 * @return true if the trie set contains elements, false otherwise.
 */
bool ts_is_empty(TrieSet *ts);

/**
 * Return the size of the trie set.
 *
 * @param ts Pointer to the trie set data structure.
 * @return The size of the trie set.
 */
size_t ts_size(TrieSet *ts);

#endif // _TRIE_SET
