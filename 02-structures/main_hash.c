#include "hash.h"
#include <stdio.h>
#include <limits.h>

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

    if (search_index(8, -9) != 7) {
        printf("ERROR INDEX SEARCH RESULT != 7\n");
        return 1;
    }
    if (search_index(8, -8) != 0) {
        printf("ERROR INDEX SEARCH RESULT != 0\n");
        return 1;
    }
    if (search_index(8, INT_MIN) != 0) {
        printf("ERROR INDEX SEARCH RESULT LIMIT NEGATIF != 0\n");
        return 1;
    }
    if (search_index(h->nb_buckets, INT_MAX) != 7) {
        printf("ERROR INDEX SEARCH RESULT LIMIT POSITIF != 7\n");
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