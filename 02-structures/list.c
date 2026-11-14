#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int list_fail_malloc = 0;

void list_free(struct List *l, size_t *nb_free) {
    if (l != NULL) {
        struct Node *p = l->head;
        while(p != NULL) {
            struct Node *tmp = p;
            p = p->next;
            free(tmp);
            if (nb_free != NULL) {
                *nb_free += 1;
            }
        }
        free(l);
        if (nb_free != NULL) {
            *nb_free += 1;
        }
    }
}

struct List *list_create(void) {
    struct List *l = NULL;
    if (list_fail_malloc == 0) {
        l = malloc(sizeof(struct List));
    }
    if (l == NULL) {
        return NULL;
    }

    l->size = 0;
    l->head = NULL;
    return l;
}

// RETURN : address of the new node, or NULL if malloc fails
// EMPTY LIST : after the push, head = n , size = 1 , n->next = NULL
// MALLOC FAILURE : the list stays the same (head and size unchanged, no node freed)
struct Node *list_push_back(struct List *l, int value) {
    struct Node *n = NULL;
    if (list_fail_malloc == 0) {
        n = malloc(sizeof(struct Node));
    }
    if (n == NULL) {
        return NULL;
    }

    n->value = value;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
    } else {
        struct Node *p = l->head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = n;
    }
    l->size++;
    return n;
}


// ┌────────────────┬────────┬──────┬────────────┬────────────┐
// │      Case      │ return │ free │ size after │ head after │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ a) 20 middle   │ 0      │ 1    │ 2          │ 10         │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ b) 10 head     │ 0      │ 1    │ 2          │ 20         │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ c) 30 last     │ 0      │ 1    │ 2          │ 10         │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ d) 99 missing  │ 1      │ 0    │ 3          │ 10         │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ e) empty list  │ 1      │ 0    │ 0          │ NULL       │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ f) l == NULL   │ 1      │ 0    │ —          │ —          │
// ├────────────────┼────────┼──────┼────────────┼────────────┤
// │ g) duplicate   │ 0      │ 1    │ 2          │ 10         │
// └────────────────┴────────┴──────┴────────────┴────────────┘
int list_delete(struct List *l, int value, size_t *nb_free) {
    if (l != NULL) {
        struct Node *target = l->head;
        struct Node *previous = NULL;
        while (target != NULL) {
            if(target->value == value) {
                if (previous == NULL) {
                    l->head = target->next;
                    free(target);
                    if (nb_free != NULL) {
                        *nb_free += 1;
                    }
                    l->size--;
                    return 0;
                } else {
                    previous->next = target->next;
                    free(target);
                    if (nb_free != NULL) {
                        *nb_free += 1;
                    }
                    l->size--;
                    return 0;
                }
            }
            previous = target;
            target = target->next;
        }
    }
    return 1;
}

struct Node *list_push_front(struct List *l, int value) {
    struct Node *n = NULL;
    if (list_fail_malloc == 0) {
        n = malloc(sizeof(struct Node));
    }
    if (n == NULL) {
        return NULL;
    }

    n->value = value;
    n->next = l->head;
    l->head = n;

    l->size++;

    return n;
}

void list_print(struct List *l) {
    struct Node *p = l->head;
    while(p != NULL) {
        printf("value:%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

int list_get(struct List *l, size_t index, int *buffer) {
    if (l != NULL && index < l->size) {
        struct Node *p = l->head;
        for(size_t i=0; i < index; i++) {
            p = p->next;
        }
        *buffer = p->value;
        return 0;
    }
    return 1;
}