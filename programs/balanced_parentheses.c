/**
 * This program reads input from the file passed as the first argument (or the
 * standard input if no argument is passed) and prints whether the parentheses
 * are balanced or not.
 */
#include <stdio.h>
#include <stdlib.h>

#include <array_stack.h>

int main(int argc, char **argv) {
    // Open file
    FILE * fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return 1;
        }
    } else {
        fp = stdin;
    }

    // Initialize the stack
    ArrayStack stack;
    as_init(&stack);

    // Read the input line by line
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int return_value = 0;
    size_t line_number = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        for (int i = 0; i < read; i++) {
            switch (line[i]) {
                case '(':
                case '[':
                case '{':
                    // Push opening parenthesis to the stack
                    as_push(&stack, (void *) line[i]);
                    break;
                case ')':
                case ']':
                case '}':
                {
                    // Pop closing parenthesis from the stack and see if it
                    // matches
                    if (as_is_empty(&stack)) {
                        fprintf(stderr, "Unbalanced closing %c at line %ld.\n",
                                line[i], line_number);
                        return_value = 1;
                        goto cleanup;
                    }
                    char stack_char = (char) as_pop(&stack);
                    if ((stack_char == '(' && line[i]!= ')') ||
                        (stack_char == '[' && line[i]!= ']') ||
                        (stack_char == '{' && line[i]!= '}')) {
                        fprintf(stderr, "Unexpected %d at line %ld.\n", line[i],
                                line_number);
                        return_value = 1;
                        goto cleanup;
                    }
                    break;
                }
            }
        }
        line_number++;
    }

    // Check if there are any unclosed parenthesis
    if (!as_is_empty(&stack)) {
        fprintf(stderr, "Unclosed parentheses.\n");
        return_value = 1;
        goto cleanup;
    }

    // Clean up
cleanup:
    as_destroy(&stack);
    fclose(fp);
    if (line) {
        free(line);
    }

    return return_value;
}