#include "bstset.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Iterator function that prints a tree element. The element should be a string.
 *
 * @param item Pointer to the tree item.
 * @param data unused.
 */
void print_element(void *item, void *data) {
    (void)(data);

    printf("%s ", (char *) item);
}

/**
 * Iterator function that frees a tree element. The element should be a string.
 *
 * @param item Pointer to the tree item.
 * @param data unused.
 */
void free_element(void *item, void *data) {
    (void)(data);

    free(item);
}

/**
 * Compares two list elements. The elements should be strings.
 *
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @return A negative value if a appears before b in lexicographical order, zero if a and b are equal or a positive
 * value if a appears after b in lexicographical order.
 */
int compare_str(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

int main(void) {
    // Read from standard input
    FILE *fp = stdin;

    // The return value for the main method
    int return_val = EXIT_SUCCESS;

    // Initialize the set
    BSTSet bs;
    if (!bsts_init(&bs, compare_str)) {
        fprintf(stderr, "Cannot initialize set.\n");
        return EXIT_FAILURE;
    }

    // Read input line by line
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Perform the set operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            printf("%s\n", bsts_is_empty(&bs) ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            printf("%zu\n", bsts_size(&bs));
        } else if (strncmp(line, "add ", strlen("add ")) == 0) {
            // Add the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!bsts_add(&bs, s)) {
                fprintf(stderr, "Cannot add to list.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
        } else if (strncmp(line, "remove_min", strlen("remove_min")) == 0) {
            free(bsts_remove_min(&bs));
        } else if (strncmp(line, "remove_max", strlen("remove_max")) == 0) {
            free(bsts_remove_max(&bs));
        } else if (strncmp(line, "remove ", strlen("remove ")) == 0) {
            // Remove the provided string
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            free(bsts_remove(&bs, str));
        } else if (strncmp(line, "contains ", strlen("contains ")) == 0) {
            // Get the string to check
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            printf("%s\n", bsts_contains(&bs, str) ? "true" : "false");
        } else if (strncmp(line, "min", strlen("min")) == 0) {
            printf("%s\n", (char *) bsts_min(&bs));
        } else if (strncmp(line, "max", strlen("max")) == 0) {
            printf("%s\n", (char *) bsts_max(&bs));
        } else if (strncmp(line, "print_reverse", strlen("print_reverse")) == 0) {
            // Print all elements in reverse order
            bsts_foreach(&bs, print_element, NULL, true);
            puts("");
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            bsts_foreach(&bs, print_element, NULL, false);
            puts("");
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

cleanup:
    // Perform cleanup
    bsts_foreach(&bs, free_element, NULL, false);
    bsts_destroy(&bs);
    free(line);
    fclose(fp);

    return return_val;
}
