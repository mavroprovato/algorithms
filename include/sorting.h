#ifndef _SORT_H
#define _SORT_H

#include <stddef.h>

typedef int (*COMPARE_FUNC) (void *first, void *second);

void insertion_sort(void *base, size_t n, size_t size, COMPARE_FUNC compare);

#endif // _SORT_H
