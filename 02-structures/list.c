#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Test switch: when not 0, every allocation of this file fails.
 *
 * Lets tests force the malloc() failure paths of list_create(),
 * list_push_back() and list_push_front().
 */
int list_fail_malloc = 0;

/**
 * @brief Frees every node of a list, then the list itself.
 *
 * @param l       List to free. May be NULL, in which case nothing happens.
 * @param nb_free Optional counter, increased by 1 for each free() call
 *                (one per node, plus one for the list). May be NULL.
 *
 * @verbatim
   Case                 free() calls
   empty list           1
   list of 3 nodes      4
   l == NULL            0
   @endverbatim
 *
 * @post l and all its nodes must no longer be used by the caller.
 */
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

/**
 * @brief Creates an empty list.
 *
 * @return The new list, with head NULL and size 0.
 * @return NULL if malloc() failed (or list_fail_malloc is set).
 *
 * @post The caller frees the list with list_free().
 */
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

/**
 * @brief Appends a value at the end of the list.
 *
 * Walks to the last node and links the new node after it, so the
 * insertion order is kept: pushing 30, 20, 10 gives 30 -> 20 -> 10.
 *
 * @param l     List to append to.
 * @param value Value to store.
 *
 * @return The address of the new node.
 * @return NULL if malloc() failed; the list is unchanged (same head,
 *         same size, no node freed).
 *
 * @par Empty list
 * After the push: head = new node, size = 1, new node's next = NULL.
 *
 * @pre l != NULL (not checked).
 */
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


/**
 * @brief Removes the first node holding a given value.
 *
 * Only the first matching node is removed; the order of the other
 * nodes does not change.
 *
 * @param l       List to remove from. May be NULL.
 * @param value   Value to look for.
 * @param nb_free Optional counter, increased by 1 when a node is freed.
 *                May be NULL.
 *
 * @return 0 if a node was found, unlinked and freed (size decreased by 1).
 * @return 1 if the value is missing, the list is empty or l is NULL;
 *         nothing is changed.
 *
 * Contract, on a 3-node list whose head holds 10:
 */
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

/**
 * @brief Inserts a value at the head of the list.
 *
 * The new node becomes the first one, so pushing 10, 20, 30 at the
 * front gives 30 -> 20 -> 10.
 *
 * @param l     List to insert into.
 * @param value Value to store.
 *
 * @return The address of the new node.
 * @return NULL if malloc() failed; the list is unchanged.
 *
 * @pre l != NULL (not checked).
 */
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

/**
 * @brief Prints every value of the list on one line.
 *
 * Each value is printed as "value:N " and the line ends with a newline.
 *
 * @param l List to print.
 *
 * @pre l != NULL (not checked).
 */
void list_print(struct List *l) {
    struct Node *p = l->head;
    while(p != NULL) {
        printf("value:%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

/**
 * @brief Reads the value of the node at a given position.
 *
 * Walks @p index nodes from the head. The status is returned and the
 * value goes out through @p buffer, because every int is a valid value.
 *
 * @param l      List to read from. May be NULL.
 * @param index  Position to read, from 0 to l->size - 1.
 * @param buffer Receives the value when the position is valid.
 *
 * @return 0 if the position is valid and *buffer was written.
 * @return 1 if l is NULL or index >= l->size; *buffer is left unchanged.
 *
 * @pre buffer != NULL, and l->size matches the number of nodes.
 */
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