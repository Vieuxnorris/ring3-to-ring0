#include "hash.h"
#include <stdio.h>

int main(void) {
    size_t nb_free = 0;
    size_t nb_free_compare = 0;

    struct Hash *h = hash_create(10);
    nb_free_compare += 2;
    if (h == NULL) {
        printf("ERROR HASH Function\n");
        hash_free(h, &nb_free);
        return 1;
    }

    struct Hash *m = hash_create(0);
    if (m != NULL) {
        printf("ERROR: hash_create aurait du echouer\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        return 1;
    }

    struct Hash *g = hash_create((size_t)1 << 60);   // 2^60 cases : le 2e malloc va échouer
    if (g != NULL) {
        printf("ERROR: hash_create aurait du echouer\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }

    hash_free(h, &nb_free);
    hash_free(g, &nb_free);
    hash_free(m, &nb_free);
    printf("Number of free nb_free: %zu nb_free_compare:%zu\n", nb_free, nb_free_compare);
    if (nb_free != nb_free_compare) {
        printf("free compare it's WRONG!\n");
        return 1;
    }
    else {
        printf("free compare it's OK!\n");
        return 0;
    }
}