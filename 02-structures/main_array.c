#include "array.h"
#include <stdio.h>

int main(void) {
    const size_t nb_pushes = 1000;
    struct Array *t = array_create(0);
    if (t == NULL) {
        return 1;
    }

    int valid;
    for(size_t i=0; i<nb_pushes; i++) {
        valid = array_push(t, (int)i-500);
        if (valid != 0) {
            printf("ERROR push at index: %zu\n", i);
            array_free(t);
            return 1;
        }
    }

    if(t->size != nb_pushes) {
        printf("ERROR size:%zu == expected:%zu\n", t->size, nb_pushes);
        array_free(t);
        return 1;
    }
    printf("size=%zu - capacity=%zu\n", t->size, t->capacity);

    int v;
    for(size_t i=0; i<nb_pushes;i++) {
        if(array_get(t, i, &v) == 0) {
            if (v != (int)i-500) {
                printf("index: %zu expected: %d, read: %d\n", i, (int)i-500, v);
                array_free(t);
                return 1;
            }
        } else {
            printf("ERROR\n");
            array_free(t);
            return 1;
        }
    }

    printf("OK: 1000 values checked.\n");
    array_free(t);
    return 0;
}