#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bheap.h"

/**
 * Compares two heap elements. The elements should be strings.
 *
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @return A negative value if a appears before b in lexicographical order, zero
 * if a and b are equal or a positive value if a appears after b in
 * lexicographical order.
 */
int compare_str(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

int main(int argc, char **argv) {
    // Check if a file was provided to be opened
    FILE *fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        fp = stdin;
    }

    // Initialize the heap
    BHeap heap;
    if (!bh_init(&heap, compare_str)) {
        fprintf(stderr, "Cannot create heap.\n");
        return EXIT_FAILURE;
    }

    int return_val = EXIT_SUCCESS;
    // Read the input line by line
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            printf("%s\n", bh_is_empty(&heap) ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            printf("%zu\n", bh_size(&heap));
        } else if (strncmp(line, "insert ", strlen("insert ")) == 0) {
            // Add the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!bh_insert(&heap, s)) {
                fprintf(stderr, "Cannot insert to heap.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
        } else if (strncmp(line, "remove_min", strlen("remove_min")) == 0) {
            char *min = bh_remove_min(&heap);
            printf("%s\n", min);
            free(min);
        } else if (strncmp(line, "peek", strlen("peek")) == 0) {
            char *min = bh_peek(&heap);
            printf("%s\n", min);
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

cleanup:
    // Cleanup resources
    bh_destroy(&heap);
    fclose(fp);
    free(line);

    return return_val;
}
