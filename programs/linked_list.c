/**
 * Test program for the linked list implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

void print_element(void *item, void *data) {
    (void)(data);

    printf("%s ", (char *) item);
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
                return_val = 1;
                goto cleanup;
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
                return_val = 1;
                goto cleanup;
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
            // Insert the string
            str = strchr(str, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                return_val = 1;
                goto cleanup;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!ll_insert(&ll, s, idx)) {
                fprintf(stderr, "Cannot insert to list.\n");
                return_val = 1;
                goto cleanup;
            }
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            ll_foreach(ll, print_element, NULL);
            puts("");
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            return_val = 1;
            goto cleanup;
        }
    }

    // Clean up
cleanup:
    free(line);
    fclose(fp);

    return return_val;
}
