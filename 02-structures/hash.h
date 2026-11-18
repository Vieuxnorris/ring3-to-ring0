#ifndef HASH_H
#define HASH_H

#include <stddef.h>

struct Entry {
    int key;
    int value;
    struct Entry *next;
};

struct Hash {
    struct Entry **buckets;
    size_t nb_buckets;
    size_t size;
};

size_t search_index(size_t nb_bucket, int key);
struct Hash *hash_create(size_t nb_buckets);
void hash_free(struct Hash *h, size_t *nb_free);
int hash_add(struct Hash *h, int valeur);

#endif