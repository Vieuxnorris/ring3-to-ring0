#include "array.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Frees a dynamic array and its data buffer.
 *
 * Releases the data buffer first, then the array structure itself.
 *
 * @param t Array to free. May be NULL, in which case nothing happens.
 *
 * @post t and t->data must no longer be used by the caller.
 */
void array_free(struct Array *t) {
    if (t != NULL) {
        free(t->data);
    }
    free(t);
}

/**
 * @brief Reads the element stored at a given index.
 *
 * The status is returned and the value goes out through @p buffer,
 * because every int is a valid element.
 *
 * @param t      Array to read from.
 * @param index  Position to read, from 0 to t->size - 1.
 * @param buffer Receives the element when the index is valid.
 *
 * @return 0 if the index is valid and *buffer was written.
 * @return 1 if index >= t->size; *buffer is left unchanged.
 *
 * @pre t != NULL and buffer != NULL (not checked).
 */
int array_get(struct Array *t, size_t index, int *buffer) {
    if (index < t->size) {
        *buffer = t->data[index];
        return 0;
    }
    return 1;
}

/**
 * @brief Appends a value at the end of the array.
 *
 * When the array is full, its capacity is doubled with realloc()
 * (or set to 1 when it was 0) before the value is stored.
 *
 * @param t     Array to append to.
 * @param value Value to store.
 *
 * @return 0 if the value was appended (size increased by 1).
 * @return 1 if realloc() failed; the array keeps its previous data,
 *         size and capacity.
 *
 * @pre t != NULL (not checked).
 */
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

/**
 * @brief Prints every element of the array on one line.
 *
 * Elements are separated by a space and followed by a newline.
 * Each element is read through array_get().
 *
 * @param t Array to print.
 *
 * @pre t != NULL (not checked).
 */
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

/**
 * @brief Creates an empty dynamic array.
 *
 * Allocates the array structure, then a buffer of @p capacity ints.
 * If the second allocation fails, the structure is freed before
 * returning, so nothing leaks.
 *
 * @param capacity Number of ints to reserve.
 *
 * @return The new array, with size 0 and the requested capacity.
 * @return NULL if an allocation failed (an error message is printed).
 *
 * @note With capacity 0, the result depends on malloc(0), which may
 *       return NULL. array_push() still works on a 0-capacity array.
 * @post The caller frees the array with array_free().
 */
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