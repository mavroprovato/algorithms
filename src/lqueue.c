
#include "lqueue.h"

bool lq_init(LQueue *lq) {
    lq->head = NULL;
    lq->tail = NULL;
    lq->size = 0;

    return true;
}

void lq_destroy(LQueue *lq) {
    ll_destroy(lq->head);
    ll_destroy(lq->tail);
}

bool lq_is_empty(LQueue *lq) {
    return lq->head == NULL;
}

size_t lq_size(LQueue *lq) {
    return lq->size;
}

bool lq_enqueue(LQueue *lq, void *item) {
    if (!ll_append(&lq->tail, item)) {
        return false;
    }
    if (lq->tail->next) {
        lq->tail = lq->tail->next;
    }
    if (!lq->head) {
        lq->head = lq->tail;
    }

    return true;
}

void *lq_dequeue(LQueue *lq) {
    void *item = NULL;
    if (lq->head) {
        item = ll_remove_first(&lq->head);
        if (!item) {
            return NULL;
        }
        lq->size--;
    }
    if (!lq->head) {
        lq->tail = NULL;
    }

    return item;
}

void *lq_peek(LQueue *lq) {
    return lq->head ? lq->head->item : NULL;
}

void lq_foreach(LQueue *lq, ITERATOR_FUNC iterator_func, void *data) {
    ll_foreach(lq->head, iterator_func, data);
}
