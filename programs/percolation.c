/**
 * Read a grid of sites from the file passed as the first argument (or the
 * standard input if no argument is passed) and print whether the grid
 * percolates or not.
 */
#include "union_find.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert a row and column index to the index of the sites array.
#define SITES_INDEX(pg, i, j) (i) * (pg)->rows + (j)
// Convert a row and column index to the index of the union-find data structure
// used in the percolation structure.
#define UF_INDEX(pg, i, j) (i) * (pg)->rows + (j) + 1

/**
 * Helper method to check if a string is composed of by whitespace characters
 * only.
 *
 * @param s The strings to check.
 * @param n The length of the string.
 * @return true if the string is empty, false otherwise.
 */
static bool is_empty(const char *s, size_t n) {
    for (size_t i = 0; i < n && s[i] != '\n'; i++) {
        if (!isspace(*s)) {
            return false;
        }
    }

    return true;
}

/**
 * Represents the grid to be checked if it percolates.
 */
typedef struct {
    /** The number of rows in the grid. */
    size_t rows;
    /** The number of columns in the grid. */
    size_t columns;
    /** The grid that holds the information weather a site is open or not. */
    // TODO: This should be converted to a bit vector, in order to save memory.
    bool *sites;
    /** The union-find data structure to efficiently check if the grid
     * percolates or not. */
    UnionFind *uf;
} PercolationGrid;

/**
 * Initialize the percolation grid.
 *
 * @param pg Pointer to the percolation grid.
 * @param rows The number of rows in the grid.
 * @param columns The number of columns in the grid.
 * @return true if the data structure has been initialized correctly, false
 * otherwise.
 */
bool pg_init(PercolationGrid *pg, size_t rows, size_t columns) {
    // Set the rows and columns
    pg->rows = rows;
    pg->columns = columns;
    // Initialize the sites grid
    pg->sites = malloc(rows * columns * sizeof(bool));
    if (!pg->sites) {
        goto error;
    }
    memset(pg->sites, 0, rows * columns * sizeof(bool));
    // Initialize the union-find data structure
    pg->uf = malloc(sizeof(UnionFind));
    if (!pg->uf) {
        goto error;
    }
    if (!uf_init(pg->uf, rows * columns + 2)) {
        goto error;
    }

    return true;

error:
    free(pg->sites);
    free(pg->uf);

    return false;
}

/**
 * Release the resources associated with the percolation grid
 *
 * @param pg The percolation grid.
 */
void pg_destroy(PercolationGrid *pg) {
    free(pg->sites);
    uf_destroy(pg->uf);
    free(pg->uf);
}

/**
 * Open a site in the grid.
 *
 * @param pg The percolation grid.
 * @param row The row of the grid to open.
 * @param column The column of the grid to open.
 * @return true if the opening of the site is successful, false otherwise.
 */
bool pg_open(PercolationGrid *pg, size_t row, size_t column) {
    if (row >= pg->rows || column >= pg->columns) {
        return false;
    }

    pg->sites[row * pg->rows + column] = true;

    size_t idx = UF_INDEX(pg, row, column);
    if (row > 0 && pg->sites[SITES_INDEX(pg, row - 1, column)]) {
        // Connect with the site above
        uf_union(pg->uf, idx, UF_INDEX(pg, row - 1, column));
    }
    if (row < pg->rows - 1 && pg->sites[SITES_INDEX(pg, row + 1, column)]) {
        // Connect with the site below
        uf_union(pg->uf, idx, UF_INDEX(pg, row + 1, column));
    }
    if (column > 0 && pg->sites[SITES_INDEX(pg, row, column - 1)]) {
        // Connect with the site to the left
        uf_union(pg->uf, idx, UF_INDEX(pg, row, column - 1));
    }
    if (column < pg->columns - 1 &&
        pg->sites[SITES_INDEX(pg, row, column + 1)]) {
        // Connect with the site to the right
        uf_union(pg->uf, idx, UF_INDEX(pg, row, column + 1));
    }
    if (row == 0) {
        // Connect with the 'dummy' top site
        uf_union(pg->uf, idx, 0);
    }
    if (row == pg->columns - 1) {
        // Connect with the 'dummy' bottom site
        uf_union(pg->uf, idx, pg->rows * pg->columns + 1);
    }

    return true;
}

/**
 * Method to check if the grid percolates or not.
 *
 * @param pg Pointer to the percolation grid.
 * @return true if the grid percolates, false otherwise.
 */
bool pg_percolates(PercolationGrid *pg) {
    return uf_connected(pg->uf, 0, pg->rows * pg->columns + 1);
}

/**
 * Read the percolation grid from the file input.
 *
 * @param fp The file input.
 * @return The percolation grid if read correctly, NULL if an error occurred.
 */
PercolationGrid *pg_read(FILE *fp) {
    // The percolation data structure
    PercolationGrid *pg = NULL;

    // Variables to read the next line from the file
    char *line = NULL;
    size_t len = 0;
    ssize_t read = -1;

    // Read the dimensions of the grid
    size_t rows = 0;
    size_t columns = 0;
    read = getline(&line, &len, fp);
    int rc = sscanf(line, "%zu %zu", &rows, &columns);
    if (rc != 2) {
        fprintf(stderr, "First row should contain the dimension of the "
                        "grid.\n");
        goto cleanup;
    }

    // Initialize the structure
    pg = malloc(sizeof(PercolationGrid));
    if (!pg) {
        fprintf(stderr, "Unable to allocate resources.\n");
        goto error_cleanup;
    }
    if (!pg_init(pg, rows, columns)) {
        fprintf(stderr, "Unable to allocate resources.\n");
        goto error_cleanup;
    }

    // Read the input line by line
    while ((read = getline(&line, &len, fp)) != -1) {
        // Skip empty lines
        if (is_empty(line, read)) {
            continue;
        }
        // Read the index of the cell to open
        size_t row = 0;
        size_t column = 0;
        rc = sscanf(line, "%zu %zu", &row, &column);
        if (rc != 2) {
            fprintf(stderr, "Invalid row and column specification\n");
            goto error_cleanup;
        }
        if (row >= rows) {
            fprintf(stderr, "Row index out of range\n");
            goto error_cleanup;
        }
        if (column >= columns) {
            fprintf(stderr, "Column index out of range\n");
            goto error_cleanup;
        }

        // Open the site
        if (!pg_open(pg, row, column)) {
            fprintf(stderr, "Could not open site %ld, %ld.\n", row, column);
            goto error_cleanup;
        }
    }

    goto cleanup;

error_cleanup:
    if (pg != NULL) {
        pg_destroy(pg);
    }
    free(pg);
    pg = NULL;

cleanup:
    free(line);

    return pg;
}

int main(int argc, char **argv) {
    // Open file
    FILE * fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        fp = stdin;
    }

    // Read the grid
    int return_value = EXIT_SUCCESS;
    PercolationGrid *pg = pg_read(fp);
    if (pg == NULL) {
        return_value = EXIT_FAILURE;
        goto cleanup;
    }

    // Print the result
    printf(pg_percolates(pg) ? "Percolates.\n" : "Does not percolate.\n");

cleanup:
    fclose(fp);
    if (pg != NULL) {
        pg_destroy(pg);
        free(pg);
    }

    return return_value;
}
