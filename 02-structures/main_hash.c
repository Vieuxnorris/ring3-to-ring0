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
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (search_index(8, -8) != 0) {
        printf("ERROR INDEX SEARCH RESULT != 0\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (search_index(8, INT_MIN) != 0) {
        printf("ERROR INDEX SEARCH RESULT LIMIT NEGATIF != 0\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (search_index(h->nb_buckets, INT_MAX) != 7) {
        printf("ERROR INDEX SEARCH RESULT LIMIT POSITIF != 7\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (hash_add(h, 13, 42) != 0) {
        printf("ERROR hash_add(13, 42)\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    nb_free_compare++;
    struct Entry *e = h->buckets[3];
    if (e == NULL) {
        printf("ERROR bucket 3 is empty\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (e->key != 13 || e->value != 42 || e->next != NULL) {
        printf("ERROR value inside bucket 3 : key=%d - value=%d - next=%p\n", e->key, e->value, e->next);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }

    if (hash_add(h, 23, 99) != 0) {
        printf("ERROR hash_add(23, 99)\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    nb_free_compare++;
    if (h->buckets[3] != e) {
        printf("ERROR bucket 3 first index diff\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (e->key != 13 || e->value != 42 || e->next == NULL) {
        printf("ERROR first value inside bucket 3 : key=%d - value=%d - next=%p\n", e->key, e->value, e->next);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (e->next->key != 23 || e->next->value != 99 || e->next->next != NULL) {
        printf("ERROR second value inside bucket 3 : key=%d - value=%d - next=%p\n", e->next->key, e->next->value, e->next->next);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }

    if (hash_add(h, 23, 100) != 0) {
        printf("ERROR hash_add(23, 100)\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (e->next->key != 23 || e->next->value != 100 || e->next->next != NULL) {
        printf("ERROR second value inside bucket 3 : key=%d - value=%d - next=%p\n", e->next->key, e->next->value, e->next->next);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (h->size != 2) {
        printf("ERROR size=2 not %zu\n", h->size);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }

    if (hash_add(NULL, 1, INT_MIN) != 1) {
        printf("ERROR hash_add(NULL, 1, INT_MIN)\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (h->size != 2) {
        printf("ERROR size=2 not %zu\n", h->size);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (hash_add(h, 1, INT_MIN) != 0) {
        printf("ERROR hash_add(h, 1, INT_MIN)\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    nb_free_compare++;
    struct Entry *t = h->buckets[1];
    if (t == NULL) {
        printf("ERROR bucket 1 is empty\n");
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (h->size != 3) {
        printf("ERROR size=3 not %zu\n", h->size);
        hash_free(h, &nb_free);
        hash_free(m, &nb_free);
        hash_free(g, &nb_free);
        return 1;
    }
    if (t->key != 1 || t->value != INT_MIN || t->next != NULL) {
        printf("ERROR second value inside bucket 1 : key=%d - value=%d - next=%p\n", t->key, t->value, t->next);
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