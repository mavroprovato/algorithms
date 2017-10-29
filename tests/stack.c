/**
 * Test program for the stack implementations.
 */
#include "astack.h"
#include "lstack.h"

#include <getopt.h>

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
    // Parse the command line arguments
    static struct option long_options[] = {
        {"linked", no_argument, 0, 'l'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    int c;
    bool linked = false;
    while ((c = getopt_long(argc, argv, "l", long_options, &option_index)) != -1) {
        switch (c) {
            case 'l':
                linked = true;
                break;
            default:
                fprintf(stderr, "Invalid option: %c\n", c);
                return EXIT_FAILURE;
        }
    }

    // Check if a file was provided to be opened
    FILE *fp;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s.\n", argv[optind]);
            return EXIT_FAILURE;
        }
    } else {
        fp = stdin;
    }

    char *line = NULL;
    int return_val = EXIT_SUCCESS;

    // Initialize the stacks
    AStack as;
    if (!as_init(&as)) {
        fprintf(stderr, "Could not create the stack data structure.\n");
        return_val = EXIT_FAILURE;
        goto cleanup;
    }
    LStack ls;
    if (!ls_init(&ls)) {
        fprintf(stderr, "Could not create the stack data structure.\n");
        return_val = EXIT_FAILURE;
        goto cleanup;
    }

    // Read the input line by line
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Perform the stack operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            bool empty = linked ? ls_is_empty(&ls) : as_is_empty(&as);
            printf("%s\n", empty ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            size_t size = linked ? ls_size(&ls) : as_size(&as);
            printf("%zu\n", size);
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
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
            if (linked) {
                if (!ls_push(&ls, s)) {
                    fprintf(stderr, "Cannot push to stack.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            } else {
                if (!as_push(&as, s)) {
                    fprintf(stderr, "Cannot push to stack.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            }
        } else if (strncmp(line, "pop", strlen("pop")) == 0) {
            char *s = linked ? ls_pop(&ls) : as_pop(&as);
            if (!s) {
                fprintf(stderr, "Cannot pop from stack.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
            printf("%s\n", s);
            free(s);
        } else if (strncmp(line, "peek", strlen("peek")) == 0) {
            char *s = linked ? ls_peek(&ls) : as_peek(&as);
            if (!s) {
                fprintf(stderr, "Cannot peek stack.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
            printf("%s\n", s);
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            if (linked) {
                ls_foreach(&ls, print_element, NULL);
            } else {
                as_foreach(&as, print_element, NULL);
            }
            puts("");
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

    // Clean up
cleanup:
    while (!as_is_empty(&as)) {
        free(as_pop(&as));
    }
    as_destroy(&as);
    while (!ls_is_empty(&ls)) {
        free(ls_pop(&ls));
    }
    ls_destroy(&ls);
    free(line);
    fclose(fp);

    return return_val;
}
