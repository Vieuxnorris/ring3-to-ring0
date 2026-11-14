#include "array.h"
#include <stdio.h>
#include <stdlib.h>


void array_free(struct Array *t) {
    if (t != NULL) {
        free(t->data);
    }
    free(t);
}

int array_get(struct Array *t, size_t index, int *buffer) {
    if (index < t->size) {
        *buffer = t->data[index];
        return 0;
    }
    return 1;
}

int array_push(struct Array *t, int value) {
    if (t->size >= t->capacity) {
        size_t new_capacity;
        if (t->capacity == 0) {
            new_capacity = 1;
        } else {
            new_capacity = t->capacity * 2;
        }
        int *tmp = realloc(t->data, new_capacity * sizeof(int));

        if (tmp != NULL) {
            t->data = tmp;
            t->capacity = new_capacity;
        } else {
            return 1;
        }
    }

    t->data[t->size] = value;
    t->size++;
    return 0;
}

void array_print(struct Array *t) {
    int v;
    for(size_t i=0; i<t->size;i++) {
        if (array_get(t, i, &v) == 0) {
            printf("%d ", v);
        } else {
            printf("Invalid index\n");
        }
    }
    printf("\n");
}

struct Array *array_create(size_t capacity) {
    struct Array *t = malloc(sizeof(struct Array));
    if (t == NULL) {
        printf("ERROR MALLOC ARRAY\n");
        return NULL;
    }

    t->data = malloc(sizeof(int) * capacity);
    if (t->data == NULL) {
        printf("ERROR MALLOC t->data\n");
        free(t);
        return NULL;
    }
    t->size = 0;
    t->capacity = capacity;
    return t;
}