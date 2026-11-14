#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

struct Array {
    int *data;
    size_t size;
    size_t capacity;
};

void array_free(struct Array *t);
int array_get(struct Array *t, size_t index, int *buffer);
int array_push(struct Array *t, int value);
void array_print(struct Array *t);
struct Array *array_create(size_t capacity);

#endif