#include <stdio.h>

#include "sorting.h"

static int compare_int(void *first, void *second) {
    int ifirst = *((int *) first);
    int isecond = *((int *) second);
    if (ifirst > isecond) {
        return 1;
    } else if (ifirst < isecond) {
        return -1;
    } else {
        return 0;
    }
}

static int compare_long(void *first, void *second) {
    long ifirst = *((long *) first);
    long isecond = *((long *) second);
    if (ifirst > isecond) {
        return 1;
    } else if (ifirst < isecond) {
        return -1;
    } else {
        return 0;
    }
}

static int compare_float(void *first, void *second) {
    float ifirst = *((float *) first);
    float isecond = *((float *) second);
    if (ifirst > isecond) {
        return 1;
    } else if (ifirst < isecond) {
        return -1;
    } else {
        return 0;
    }
}

static int compare_double(void *first, void *second) {
    double ifirst = *((double *) first);
    double isecond = *((double *) second);
    if (ifirst > isecond) {
        return 1;
    } else if (ifirst < isecond) {
        return -1;
    } else {
        return 0;
    }
}

int main(void) {
    int test_i[] = { 54 , 34, 66, 1 , 93, 44};
    insertion_sort(test_i, 6, sizeof(int), compare_int);
    for (size_t i = 0; i < 6; i++) {
        printf("%d ", test_i[i]);
    }
    printf("\n");

    long test_l[] = { 54 , 34, 66, 1 , 93, 44};
    insertion_sort(test_l, 6, sizeof(long), compare_long);
    for (size_t i = 0; i < 6; i++) {
        printf("%ld ", test_l[i]);
    }
    printf("\n");

    float test_f[] = { 5.4 , 3.4, 6.6, 1. , 9.3, 4.4};
    insertion_sort(test_f, 6, sizeof(float), compare_float);
    for (size_t i = 0; i < 6; i++) {
        printf("%.2f ", test_f[i]);
    }
    printf("\n");

    double test_d[] = { 5.4 , 3.4, 6.6, 1. , 9.3, 4.4};
    insertion_sort(test_d, 6, sizeof(double), compare_double);
    for (size_t i = 0; i < 6; i++) {
        printf("%.2f ", test_d[i]);
    }
    printf("\n");

    return 0;
}
