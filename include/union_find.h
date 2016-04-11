#ifndef _UNION_FIND_H
#define _UNION_FIND_H

#include <stdbool.h>
#include <stddef.h>

/**
 * The union find data structure.
 */
typedef struct {
    /** Identifiers of the parent of the element. */
    size_t *parent;
    /** Number of elements in the component rooted at i. */
    size_t *size;
    /** The number of elements. */
    size_t n;
    /** The number of components. */
    size_t components;
} UnionFind;

/**
 * Initializes the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be initialized.
 * @param n The number of elements in the set. It must be greater than zero.
 * @return true if the data structure was initialized correctly.
 */
bool uf_create(UnionFind *uf, size_t n);

/**
 * Frees resources associated with the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be freed.
 */
void uf_destroy(UnionFind *uf);

/**
 * Join the subsets that two elements belong to.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The identifier of the first element.
 * @param q The identifier of the second element.
 * @return true if both element identifiers are in range.
 */
bool uf_union(UnionFind *uf, size_t p, size_t q);

/**
 * Return the identifier of the connected component for an element.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The identifier of the element.
 * @return The identifier of the connected component, or SIZE_MAX if the element
 * identifiers are in range.
 */
size_t uf_find(UnionFind *uf, size_t p);

/**
 * Check if two components are connected.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The identifier of the first element.
 * @param q The identifier of the second element.
 * @return true if the two components are connected.
 */
bool uf_connected(UnionFind *uf, size_t p, size_t q);

/**
 * Return the number of components.
 *
 * @param uf Pointer to the union find data structure.
 * @return The number of components.
 */
size_t uf_component_count(UnionFind *uf);


#endif // _UNION_FIND_H
