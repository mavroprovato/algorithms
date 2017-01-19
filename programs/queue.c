/**
 * Test program for the queue implementations.
 */
#include "aqueue.h"
#include "linked_queue.h"

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
    int c = -1;
    bool linked = false;
    while ((c = getopt_long(argc, argv, "l", long_options, &option_index)) != -1) {
        switch (c) {
            case 'l':
                linked = true;
                break;
            default:
                return 0;
        }
    }

    // Check if a file was provided to be opened
    FILE *fp;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s.\n", argv[optind]);
            return 1;
        }
    } else {
        fp = stdin;
    }

    char *line = NULL;
    int return_val = 0;

    // Initialize the queues
    AQueue aq;
    if (!aq_init(&aq)) {
        fprintf(stderr, "Could not create the queue data structure.\n");
        return_val = 1;
        goto cleanup;
    }
    LinkedQueue lq;
    if (!lq_init(&lq)) {
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
            bool empty = linked ? lq_is_empty(&lq) : aq_is_empty(&aq);
            printf("%s\n", empty ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            size_t size = linked ? lq_size(&lq) : aq_size(&aq);
            printf("%zu\n", size);
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
            if (linked) {
                if (!lq_enqueue(&lq, s)) {
                    fprintf(stderr, "Cannot enqueue element.\n");
                    return_val = 1;
                    goto cleanup;
                }
            } else {
                if (!aq_enqueue(&aq, s)) {
                    fprintf(stderr, "Cannot enqueue element.\n");
                    return_val = 1;
                    goto cleanup;
                }
            }
        } else if (strncmp(line, "dequeue", strlen("dequeue")) == 0) {
            char *s = linked ? lq_dequeue(&lq) : aq_dequeue(&aq);
            if (!s) {
                fprintf(stderr, "Cannot dequeue element.\n");
                return_val = 1;
                goto cleanup;
            }
            printf("%s\n", s);
            free(s);
        } else if (strncmp(line, "peek", strlen("peek")) == 0) {
            char *s = linked ? lq_peek(&lq) : aq_peek(&aq);
            if (!s) {
                fprintf(stderr, "Cannot peek queue.\n");
                return_val = 1;
                goto cleanup;
            }
            printf("%s\n", s);
        } else if (strncmp(line, "print", strlen("print")) == 0) {
            // Print all elements
            if (linked) {
                lq_foreach(&lq, print_element, NULL);
            } else {
                aq_foreach(&aq, print_element, NULL);
            }
            puts("");
        } else {
            fprintf(stderr, "Invalid command: %.*s.\n", (int) read - 1, line);
            continue;
        }
    }

    // Clean up
cleanup:
    while (!aq_is_empty(&aq)) {
        free(aq_dequeue(&aq));
    }
    aq_destroy(&aq);
    while (!lq_is_empty(&lq)) {
        free(lq_dequeue(&lq));
    }
    lq_destroy(&lq);
    free(line);
    fclose(fp);

    return return_val;
}
