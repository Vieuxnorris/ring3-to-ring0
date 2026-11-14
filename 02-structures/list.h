#ifndef LIST_H
#define LIST_H

#include <stddef.h>

extern int list_fail_malloc;

struct Node {
    int value;
    struct Node *next;
};

struct List {
    size_t size;
    struct Node *head;
};

void list_free(struct List *l, size_t *nb_free);
struct List *list_create(void);
int list_get(struct List *l, size_t index, int *buffer);
struct Node *list_push_front(struct List *l, int value);
struct Node *list_push_back(struct List *l, int value);
int list_delete(struct List *l, int value, size_t *nb_free);
void list_print(struct List *l);

#endif