/**
 * Test program for the array stack implementation.
 */
#include "array_stack.h"

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

    // Initialize the stack
    char *line = NULL;
    int return_val = 0;
    ArrayStack stack;
    if (!as_init(&stack)) {
        fprintf(stderr, "Could not create the stack data structure.\n");
        return_val = 1;
        goto cleanup;
    }

    // Read the input line by line
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Perform the stack operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            printf("%s\n", as_is_empty(&stack) ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            printf("%zu\n", as_size(&stack));
        } else if (strncmp(line, "push", strlen("push")) == 0) {
            // Find the command
            char *space_idx = strchr(line, ' ');
            if (!space_idx) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            // Find and push the string
            char *s = strndup(space_idx + 1, strlen(space_idx) - 2);
            if (!s) {
                fprintf(stderr, "Cannot allocate memory.\n");
                return_val = 1;
                goto cleanup;
            }
            if (!as_push(&stack, s)) {
                fprintf(stderr, "Cannot push to stack.\n");
                return_val = 1;
                goto cleanup;
            }
        } else if (strncmp(line, "pop", strlen("pop")) == 0) {
            char *s = as_pop(&stack);
            if (!s) {
                fprintf(stderr, "Cannot pop from stack.\n");
                return_val = 1;
                goto cleanup;
            }
            printf("%s\n", s);
            free(s);
        } else if (strncmp(line, "peek", strlen("peek")) == 0) {
            char *s = as_peek(&stack);
            if (!s) {
                fprintf(stderr, "Cannot peek stack.\n");
                return_val = 1;
                goto cleanup;
            }
            printf("%s\n", s);
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            as_foreach(&stack, print_element, NULL);
            puts("");
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

    // Clean up
cleanup:
    as_destroy(&stack);
    free(line);
    fclose(fp);

    return return_val;
}
