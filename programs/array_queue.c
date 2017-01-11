/**
 * Test program for the array queue implementation.
 */
#include "array_queue.h"

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

    // Initialize the queue
    char *line = NULL;
    int return_val = 0;
    ArrayQueue queue;
    if (!aq_init(&queue)) {
        fprintf(stderr, "Could not create the queue data structure.\n");
        return_val = 1;
        goto cleanup;
    }

    // Read the input line by line
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Perform the queue operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            printf("%s\n", aq_is_empty(&queue) ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            printf("%zu\n", aq_size(&queue));
        } else if (strncmp(line, "enqueue ", strlen("enqueue ")) == 0) {
            // Find the string
            char *space_idx = strchr(line, ' ');
            if (!space_idx) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            // Find and enqueue the string
            char *s = strndup(space_idx + 1, strlen(space_idx) - 2);
            if (!s) {
                fprintf(stderr, "Cannot allocate memory.\n");
                return_val = 1;
                goto cleanup;
            }
            if (!aq_enqueue(&queue, s)) {
                fprintf(stderr, "Cannot enqueue element.\n");
                return_val = 1;
                goto cleanup;
            }
        } else if (strncmp(line, "dequeue", strlen("dequeue")) == 0) {
            char *s = aq_dequeue(&queue);
            if (!s) {
                fprintf(stderr, "Cannot dequeue element.\n");
                return_val = 1;
                goto cleanup;
            }
            printf("%s\n", s);
            free(s);
        } else if (strncmp(line, "peek", strlen("peek")) == 0) {
            char *s = aq_peek(&queue);
            if (!s) {
                fprintf(stderr, "Cannot peek queue.\n");
                return_val = 1;
                goto cleanup;
            }
            printf("%s\n", s);
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            aq_foreach(&queue, print_element, NULL);
            puts("");
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

    // Clean up
cleanup:
    aq_destroy(&queue);
    free(line);
    fclose(fp);

    return return_val;
}
