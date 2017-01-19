
#include "lstack.h"

bool ls_init(LStack *ls) {
    ls->ll = NULL;
    ls->size = 0;

    return true;
}

void ls_destroy(LStack *ls) {
    ll_destroy(ls->ll);
}

bool ls_is_empty(LStack *ls) {
    return ll_is_empty(ls->ll);
}

size_t ls_size(LStack *ls) {
    return ls->size;
}

bool ls_push(LStack *ls, void *item) {
    bool success = ll_prepend(&ls->ll, item);
    if (success) {
        ls->size++;
    }

    return success;
}

void *ls_pop(LStack *ls) {
    void *item = ll_remove_first(&ls->ll);
    if (item) {
        ls->size--;
    }

    return item;
}

void *ls_peek(LStack *ls) {
    return ls->ll ? ls->ll->item : NULL;
}

void ls_foreach(LStack *ls, ITERATOR_FUNC iterator_func, void *data) {
    ll_foreach(ls->ll, iterator_func, data);
}
