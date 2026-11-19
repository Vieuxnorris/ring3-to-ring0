#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

// return NULL : ERROR MALLOC h == NULL
// return NULL : ERROR NB_BUCKETS == 0
// return NULL : ERROR MALLOC ENTRY LIST h->buckets == NULL
// return struct Hash *h : allocation Hash table
struct Hash *hash_create(size_t nb_buckets) {
    if (nb_buckets == 0) {
        printf("ERROR NB_BUCKETS: %zu\n", nb_buckets);
        return NULL;
    }

    struct Hash *h = malloc(sizeof(struct Hash));

    if (h == NULL) {
        printf("ERROR MALLOC HASH\n");
        return NULL;
    }

    h->nb_buckets = nb_buckets;
    h->size = 0;
    h->buckets = malloc(sizeof(struct Entry *) * h->nb_buckets);

    if (h->buckets == NULL) {
        printf("ERROR MALLOC ENTRY LIST\n");
        hash_free(h, NULL);
        return NULL;
    }
    for(size_t i = 0; i < h->nb_buckets; i++) {
        h->buckets[i] = NULL;
    }
    return h;
}

//                                          free d'Entry   free(buckets)   free(h)   total
//   table de 10 cases, toutes vides          0            1           1     2
//   table de 8 cases, 2 clés dans la case 3  2            1           1     4
void hash_free(struct Hash *h, size_t *nb_free) {
    if (h != NULL) {
        if (h->buckets != NULL) {
            for (size_t i = 0; i < h->nb_buckets; i++) {
                if (h->buckets[i] != NULL) {
                    struct Entry *e = h->buckets[i];
                    while(e != NULL) {
                        struct Entry *tmp = e;
                        e = e->next;
                        free(tmp);
                        if (nb_free != NULL) {
                            *nb_free += 1;
                        }
                    }
                }
            }
            free(h->buckets);
            if (nb_free != NULL) {
                *nb_free += 1;
            }
        }
        free(h);
        if (nb_free != NULL) {
            *nb_free += 1;
        }
    }
}

size_t search_index(size_t nb_bucket, int key) {
    if (key >= 0) {
        return key % nb_bucket;
    } else {
        size_t distance = -(key + 1); // -(-9 + 1) = 8
        distance++; // 8 + 1 = 9
        size_t r = distance % nb_bucket; // r = 9%8 = 1
        if (r == 0) {
            return 0;
        }
        return nb_bucket - r; // 8 - 1
    }
}

int hash_add(struct Hash *h, int key, int value) {
    if (h != NULL) {
        int index = search_index(h->nb_buckets, key);
        struct Entry *e = h->buckets[index];
        if (e != NULL) {
            struct Entry *previous = NULL;
            while(e->next != NULL) {
                previous = e;
                e = e->next;
            }
            e->key = key;
            e->value = value;
            previous->next = e;
        } else {
            e->key = key;
            e->value = value;
            e->next = NULL;
        }
    }
    return 1;
}