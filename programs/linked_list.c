/**
 * Test program for the linked list implementation.
 */
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Iterator function that prints a list element. The element should be a string.
 *
 * @param item Pointer to the list item.
 * @param data unused.
 */
void print_element(void *item, void *data) {
    (void)(data);

    printf("%s ", (char *) item);
}

/**
 * Compares two list elements. The elements should be strings.
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
    // Open file
    FILE * fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s.\n", argv[1]);
            return 1;
        }
    } else {
        fp = stdin;
    }

    int return_val = 0;
    LinkedList *ll = NULL;

    // Read the input line by line
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Perform the queue operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            printf("%s\n", ll_is_empty(ll) ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            printf("%zu\n", ll_size(ll));
        } else if (strncmp(line, "prepend", strlen("prepend")) == 0) {
            // Prepend the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!ll_prepend(&ll, s)) {
                fprintf(stderr, "Cannot prepend to list.\n");
                return_val = 1;
                goto cleanup;
            }
        } else if (strncmp(line, "append", strlen("append")) == 0) {
            // Append the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!ll_append(&ll, s)) {
                fprintf(stderr, "Cannot append to list.\n");
                return_val = 1;
                goto cleanup;
            }
        } else if (strncmp(line, "insert", strlen("insert")) == 0) {
            // Get the position to insert
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            int idx = -1;
            int rc = sscanf(str, "%d", &idx);
            if (rc != 1 || idx < 0) {
                fprintf(stderr, "Invalid index.\n");
                continue;
            }
            // Insert the string
            str = strchr(str, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!ll_insert(&ll, s, idx)) {
                fprintf(stderr, "Cannot insert to list.\n");
                return_val = 1;
                goto cleanup;
            }
        } else if (strncmp(line, "remove_first", strlen("remove_first")) == 0) {
            // Remove first element
            free(ll_remove_first(&ll));
        } else if (strncmp(line, "remove_last", strlen("remove_last")) == 0) {
            // Remove last element
            free(ll_remove_last(&ll));
        } else if (strncmp(line, "remove ", strlen("remove ")) == 0) {
            // Get the position of the element to remove
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                return_val = 1;
                goto cleanup;
            }
            str++;
            int idx = -1;
            int rc = sscanf(str, "%d", &idx);
            if (rc != 1 || idx < 0) {
                fprintf(stderr, "Invalid index.\n");
                return_val = 1;
                goto cleanup;
            }
            // Remove the element
            free(ll_remove(&ll, idx));
        } else if (strncmp(line, "remove_item", strlen("remove_item")) == 0) {
            // Get the element to remove
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            // Remove the element
            free(ll_remove_item(&ll, str, compare_str));
        } else if (strncmp(line, "contains", strlen("contains")) == 0) {
            // Get the string to check
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            printf("%s\n", ll_contains(ll, str, compare_str) ? "true" :
                                                               "false");
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            ll_foreach(ll, print_element, NULL);
            puts("");
        } else if (strncmp(line, "reverse", strlen("reverse")) == 0) {
            // Reverse the list
            ll_reverse(&ll);
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

    // Clean up
cleanup:
    while (!ll_is_empty(ll)) {
        free(ll_remove_first(&ll));
    }
    free(line);
    fclose(fp);

    return return_val;
}
