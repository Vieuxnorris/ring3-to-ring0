#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Creates an empty hash table.
 *
 * Allocates the table, then an array of @p nb_buckets bucket pointers,
 * all set to NULL (empty buckets). If the bucket array cannot be
 * allocated, the table already allocated is freed before returning.
 *
 * @param nb_buckets Number of buckets. Must be greater than zero.
 *
 * @return The new table, with size 0.
 * @return NULL if nb_buckets == 0 ("ERROR NB_BUCKETS"), if the table
 *         allocation failed ("ERROR MALLOC HASH") or if the bucket array
 *         allocation failed ("ERROR MALLOC ENTRY LIST").
 *
 * @post The caller frees the table with hash_free().
 */
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

/**
 * @brief Frees every entry of every bucket, then the bucket array,
 *        then the table.
 *
 * Also works on a table whose bucket array is NULL (used by
 * hash_create() when that allocation fails).
 *
 * @param h       Table to free. May be NULL, in which case nothing happens.
 * @param nb_free Optional counter, increased by 1 for each free() call.
 *                May be NULL.
 *
 * @post h, its bucket array and all its entries must no longer be used.
 */
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


/**
 * @brief Computes the bucket index for a given key.
 *
 * Maps an integer key to a valid bucket index using the modulo
 * operation. Negative keys are handled separately to ensure
 * the resulting index is always within the bucket array bounds.
 *
 * The calculation safely handles all integer values, including
 * INT_MIN, without causing signed integer overflow.
 *
 * @param nb_bucket Number of buckets in the hash table.
 *                  Must be greater than zero.
 * @param key Integer key to hash (positive or negative).
 *
 * @return The computed bucket index in the range
 *         [0, nb_bucket - 1].
 *
 * @pre nb_bucket > 0.
 */
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

/**
 * @brief Inserts or updates a key-value pair in the hash table.
 *
 * Computes the bucket index using search_index() and traverses
 * the corresponding linked list to find an existing key.
 *
 * If the key already exists, its value is updated without
 * allocating a new entry or changing the table size.
 *
 * If the key does not exist, a new entry is allocated and
 * appended to the end of the bucket's linked list.
 * The table size is then incremented.
 *
 * @param h Pointer to the hash table.
 * @param key Integer key to insert or update.
 * @param value Integer value associated with the key.
 *
 * @return 0 on successful insertion or update.
 * @return 1 if the hash table pointer is NULL or
 *         memory allocation fails.
 *
 * @pre h->nb_buckets > 0 and h->buckets points to
 *      a valid bucket array when h is not NULL.
 *
 * @note Hash collisions are resolved using separate chaining
 *       with singly linked lists.
 */
int hash_add(struct Hash *h, int key, int value) {
    if (h != NULL) {
        size_t index = search_index(h->nb_buckets, key);
        struct Entry *current = h->buckets[index]; // target = [13]

        struct Entry *previous = NULL;
        while(current != NULL) {
            previous = current;
            if (previous->key == key) {
                previous->value = value;
                return 0;
            }
            current = current->next; // target = [23]
        }
        struct Entry *new = malloc(sizeof(struct Entry)); // {key=??, value=??, next=??}
        if (new == NULL) {
            return 1;
        }
        new->key = key; // new = [33]
        new->value = value;
        new->next = NULL;
        if (previous == NULL) {
            h->buckets[index] = new;
        } else {
            previous->next = new; // target = [23] --next--> new [33]
        }
        h->size += 1;
        return 0;
    }
    return 1;
}

struct Entry *hash_get(struct Hash *h, int key, int value) {
    if (h != NULL) {
        size_t index = search_index(h->nb_buckets, key);
        struct Entry *current = h->buckets[index];

        while (current != NULL) {
            if (current->key == key && current->value == value) {
                return current;
            }
        }
        return NULL;
    }
    return NULL;
}