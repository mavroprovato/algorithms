#include "trieset.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Read from standard input
    FILE *fp = stdin;

    // The return value for the main method
    int return_val = EXIT_SUCCESS;

    // Initialize the set
    TrieSet ts;
    if (!ts_init(&ts)) {
        fprintf(stderr, "Cannot initialize set.\n");
        return EXIT_FAILURE;
    }

    // Read input line by line
    char *line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {
        // Perform the set operation based on the command
        if (strncmp(line, "is_empty", strlen("is_empty")) == 0) {
            printf("%s\n", ts_is_empty(&ts) ? "empty" : "not empty");
        } else if (strncmp(line, "size", strlen("size")) == 0) {
            printf("%zu\n", ts_size(&ts));
        } else if (strncmp(line, "add ", strlen("add ")) == 0) {
            // Add the string after the command
            char *str = strchr(line, ' ');
            if (!str) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            str++;
            str[strlen(str) - 1] = '\0';
            if (!ts_add(&ts, str)) {
                fprintf(stderr, "Cannot add to set.\n");
                return_val = EXIT_FAILURE;
                goto cleanup;
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
            printf("%s\n", ts_contains(&ts, str) ? "true" : "false");
        }
    }

cleanup:
    ts_destroy(&ts);
    free(line);
    fclose(fp);

    return return_val;
}
