#include <stdio.h>

#include "array_queue.h"


int main(void) {
    char *strings[10];

    strings[0] = "one";
    strings[1] = "two";
    strings[2] = "three";
    strings[3] = "four";
    strings[4] = "five";
    strings[5] = "six";
    strings[6] = "seven";
    strings[7] = "eight";
    strings[8] = "nine";
    strings[9] = "ten";

    ArrayQueue aq;
    aq_init(&aq, 4);

    for (int i = 0; i < 10; i++) {
        aq_enqueue(&aq, strings[i]);
    }

    printf("Queue size is %ld\n", aq_size(&aq));
    printf("Last element added is %s\n", (char *) aq_peek(&aq));
    while (!aq_is_empty(&aq)) {
        printf("Popping element: %s\n", (char *) aq_dequeue(&aq));
        printf("Queue size is %ld\n", aq_size(&aq));
    }
    printf("Queue is empty: %s\n", aq_is_empty(&aq) ? "true" : "false");

    aq_destroy(&aq);

    return 0;
}
