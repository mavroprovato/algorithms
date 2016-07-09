#ifndef _UNION_FIND_H
#define _UNION_FIND_H

#include <stdbool.h>
#include <stddef.h>

/**
 * The uninon find data structure.
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
 * @param n The number of objects in the set.
 */
void uf_create(UnionFind *uf, size_t n);

/**
 * Frees resources associated with the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be freed.
 */
void uf_destroy(UnionFind *uf);

/**
 * Connect two elements.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The indetifier of the first element.
 * @param q The indetifier of the second element.
 */
void uf_union(UnionFind *uf, size_t p, size_t q);

/**
 * Return the indetifier of the connected component for an element.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The indetifier of the element.
 * @return The indetifier of the connected component.
 */
size_t uf_find(UnionFind *uf, size_t p);

/**
 * Check if two componenets are connected.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The indetifier of the first element.
 * @param q The indetifier of the second element.
 * @return true if the two componenets are connected.
 */
bool uf_connected(UnionFind *uf, int p, int q);

/**
 * Return the number of components.
 *
 * @param uf Pointer to the union find data structure.
 * @return The number of components.
 */
size_t uf_component_count(UnionFind *uf);

#endif // _UNION_FIND_H
