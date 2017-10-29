/**
 * Test program for the linked list and doubly linked list implementations.
 */
#include "llist.h"
#include "dllist.h"

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
    // Parse the command line arguments
    static struct option long_options[] = {
        {"doubly-linked", no_argument, 0, 'd'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    int c;
    bool doubly_linked = false;
    while ((c = getopt_long(argc, argv, "d", long_options, &option_index)) != -1) {
        switch (c) {
            case 'd':
                doubly_linked = true;
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

    int return_val = EXIT_SUCCESS;

    LList llist;
    if (!ll_init(&llist)) {
        fprintf(stderr, "Could not create the linked list data structure.\n");
        return_val = EXIT_FAILURE;
        goto cleanup;
    }
    DLList dllist;
    if (!dll_init(&dllist)) {
        fprintf(stderr, "Could not create the linked list data structure.\n");
        return_val = EXIT_FAILURE;
        goto cleanup;
    }

    // Read the input line by line
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        // Perform the queue operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            bool is_empty;
            if (doubly_linked) {
                is_empty = dll_is_empty(&dllist);
            } else {
                is_empty = ll_is_empty(&llist);
            }
            printf("%s\n", is_empty ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            size_t size;
            if (doubly_linked) {
                size = dll_size(&dllist);
            } else {
                size = ll_size(&llist);
            }
            printf("%zu\n", size);
        } else if (strncmp(line, "prepend ", strlen("prepend ")) == 0) {
            // Prepend the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!s) {
                fprintf(stderr, "Cannot allocate memory.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
            if (doubly_linked) {
                if (!dll_prepend(&dllist, s)) {
                    fprintf(stderr, "Cannot prepend to list.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            } else {
                if (!ll_prepend(&llist, s)) {
                    fprintf(stderr, "Cannot prepend to list.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            }
        } else if (strncmp(line, "append ", strlen("append ")) == 0) {
            // Append the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            char *s = strndup(str, strlen(str) - 1);
            if (!s) {
                fprintf(stderr, "Cannot allocate memory.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
            if (doubly_linked) {
                if (!dll_append(&dllist, s)) {
                    fprintf(stderr, "Cannot append to list.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            } else {
                if (!ll_append(&llist, s)) {
                    fprintf(stderr, "Cannot append to list.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            }
        } else if (strncmp(line, "insert ", strlen("insert ")) == 0) {
            // Get the position to insert
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            size_t idx = 0;
            int rc = sscanf(str, "%zu", &idx);
            if (rc != 1) {
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
            if (!s) {
                fprintf(stderr, "Cannot allocate memory.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
            }
            if (doubly_linked) {
                if (!dll_insert(&dllist, s, idx)) {
                    fprintf(stderr, "Cannot insert to list.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            } else {
                if (!ll_insert(&llist, s, idx)) {
                    fprintf(stderr, "Cannot insert to list.\n");
                    return_val = EXIT_FAILURE;
                    goto cleanup;
                }
            }
        } else if (strncmp(line, "remove_first", strlen("remove_first")) == 0) {
            // Remove first element
            if (doubly_linked) {
                free(dll_remove_first(&dllist));
            } else {
                free(ll_remove_first(&llist));
            }
        } else if (strncmp(line, "remove_last", strlen("remove_last")) == 0) {
            // Remove last element
            if (doubly_linked) {
                free(dll_remove_last(&dllist));
            } else {
                free(ll_remove_last(&llist));
            }
        } else if (strncmp(line, "remove ", strlen("remove ")) == 0) {
            // Get the position of the element to remove
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            size_t idx = 0;
            int rc = sscanf(str, "%zu", &idx);
            if (rc != 1) {
                fprintf(stderr, "Invalid index.\n");
                continue;
            }
            // Remove the element
            if (doubly_linked) {
                free(dll_remove(&dllist, idx));
            } else {
                free(ll_remove(&llist, idx));
            }
        } else if (strncmp(line, "remove_item ", strlen("remove_item ")) == 0) {
            // Get the element to remove
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            // Remove the element
            if (doubly_linked) {
                free(dll_remove_item(&dllist, str, compare_str));
            } else {
                free(ll_remove_item(&llist, str, compare_str));
            }
        } else if (strncmp(line, "contains ", strlen("contains ")) == 0) {
            // Get the string to check
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            bool contains;
            if (doubly_linked) {
                contains = dll_contains(&dllist, str, compare_str);
            } else {
                contains = ll_contains(&llist, str, compare_str);
            }
            printf("%s\n", contains ? "true" : "false");
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            if (doubly_linked) {
                dll_foreach(&dllist, print_element, NULL, false);
            } else {
                ll_foreach(&llist, print_element, NULL);
            }
            puts("");
        } else if (strncmp(line, "reverse", strlen("reverse")) == 0) {
            // Reverse the list
            if (doubly_linked) {
                dll_reverse(&dllist);
            } else {
                ll_reverse(&llist);
            }
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

    // Clean up
cleanup:
    if (doubly_linked) {
        while (!dll_is_empty(&dllist)) {
            free(dll_remove_first(&dllist));
        }
        dll_destroy(&dllist);
    } else {
        while (!ll_is_empty(&llist)) {
            free(ll_remove_first(&llist));
        }
        ll_destroy(&llist);
    }

    free(line);
    fclose(fp);

    return return_val;
}
