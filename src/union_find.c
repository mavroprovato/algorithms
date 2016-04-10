#include "union_find.h"

#include <stdlib.h>
#include <string.h>

/**
 * Initializes the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be initialized.
 * @param n The number of elements in the set.
 */
void uf_create(UnionFind *uf, size_t n) {
    uf->parent = malloc(n * sizeof(size_t));
    for (size_t i = 0; i < n; i++) {
        uf->parent[i] = i;
    }
    uf->size = malloc(n * sizeof(size_t));
    memset(uf->size, 0, n * sizeof(size_t));
    uf->n = n;
}

/**
 * Frees resources assiciated with the union find data structure.
 *
 * @param uf Pointer to the union find data structure to be freed.
 */
void uf_destroy(UnionFind *uf) {
    free(uf->parent);
    free(uf->size);
}

/**
 * Connect two elements.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The indetifier of the first element.
 * @param q The indetifier of the second element.
 */
void uf_union(UnionFind *uf, size_t p, size_t q) {
    size_t i = uf_find(uf, p);
    size_t j = uf_find(uf, q);
    if (i != j) {
        if (uf->size[i] < uf->size[j]) {
            uf->parent[i] = j;
            uf->size[i] += uf->size[j];
        } else {
            uf->parent[j] = i;
            uf->size[j] += uf->size[i];
        }
        uf->components--;
    }
}

/**
 * Return the indetifier of the connected component for an element.
 *
 * @param uf Pointer to the union find data structure.
 * @param p The indetifier of the element.
 * @return The indetifier of the connected component.
 */
size_t uf_find(UnionFind *uf, size_t p) {
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
 * @param p The indetifier of the first element.
 * @param q The indetifier of the second element.
 * @return true if the two components are connected.
 */
bool uf_connected(UnionFind *uf, int p, int q) {
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
