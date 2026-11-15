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

struct Hash *hash_create(size_t nb_buckets);
void hash_free(struct Hash *h, size_t *nb_free);

#endif