#ifndef _COMMON_H
#define _COMMON_H

/**
 * Prototype for a function that compares two elements.
 *
 * @param first The first element.
 * @param second The second element.
 * @return A positive integer if the first element is greater that the second,
 * a negative integer if the first element is less than the second, or zero if
 * they are equal.
 */
typedef int (*COMPARE_FUNC) (const void *first, const void *second);

/**
 * Prototype for a function used to iterate the linked list.
 *
 * @param item The current item.
 * @param data Pointer to the custom user data. Can be NULL.
 */
typedef void (*ITERATOR_FUNC) (void *item, void *data);

#endif // _COMMON_H
