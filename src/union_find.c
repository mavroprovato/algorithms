#include "union_find.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Initializes the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be initialized.
 * @param n The number of elements in the set. It must be greater than zero.
 * @return true if the data structure was initialized correctly.
 */
bool uf_init(UnionFind *uf, size_t n) {
    if (n == 0) {
        return false;
    }
    // Allocate memory
    uf->parent = malloc(n * sizeof(size_t));
    if (!uf->parent) {
        return false;
    }
    uf->size = malloc(n * sizeof(size_t));
    if (!uf->size) {
        free(uf->parent);
        return false;
    }
    // Initialize members
    for (size_t i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->size[i] = 1;
    }
    uf->n = n;

    return true;
}

/**
 * Frees resources associated with the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be freed.
 */
void uf_destroy(UnionFind *uf) {
    free(uf->parent);
    free(uf->size);
}

/**
 * Join the subsets that two elements belong to.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The identifier of the first element.
 * @param q The identifier of the second element.
 * @return true if both element identifiers are in range.
 */
bool uf_union(UnionFind *uf, size_t p, size_t q) {
    if (p >= uf->n || q >= uf->n) {
        return false;
    }
    size_t i = uf_find(uf, p);
    size_t j = uf_find(uf, q);
    if (i != j) {
        if (uf->size[i] < uf->size[j]) {
            uf->parent[i] = j;
            uf->size[j] += uf->size[i];
        } else {
            uf->parent[j] = i;
            uf->size[i] += uf->size[j];
        }
        uf->components--;
    }

    return true;
}

/**
 * Return the identifier of the connected component for an element.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The identifier of the element.
 * @return The identifier of the connected component, or SIZE_MAX if the element
 * identifiers are in range.
 */
size_t uf_find(UnionFind *uf, size_t p) {
    if (p >= uf->n) {
        return SIZE_MAX;
    }
    // Find the root
    size_t root = p;
    while (root != uf->parent[root]) {
        root = uf->parent[root];
    }
    // Path compression
    while (p != root) {
        size_t parent_p = uf->parent[p];
        uf->parent[p] = root;
        p = parent_p;
    }

    return root;
}

/**
 * Check if two components are connected.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The identifier of the first element.
 * @param q The identifier of the second element.
 * @return true if the two components are connected.
 */
bool uf_connected(UnionFind *uf, size_t p, size_t q) {
    if (p >= uf->n || q >= uf->n) {
        return false;
    }
    return uf_find(uf, p) == uf_find(uf, q);
}

/**
 * Return the number of components.
 *
 * @param uf Pointer to the union find data structure.
 * @return The number of components.
 */
size_t uf_component_count(UnionFind *uf) {
    return uf->components;
}
