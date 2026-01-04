#ifndef HASH_TABLES_H
#define HASH_TABLES_H

#include <stddef.h>
#include <stdint.h>

/*
 * Simple open-addressing hash table:
 * - keys: uint64_t
 * - values: int
 * - linear probing
 * - tombstones for deletion
 *
 * states[i]:
 *   0 = empty
 *   1 = filled
 *   2 = deleted (tombstone)
 */
typedef struct {
    size_t cap;         // capacity (power of two)
    size_t size;        // number of FILLED slots
    size_t tombstones;  // number of DELETED slots

    uint64_t *keys;
    int *values;
    uint8_t *states;
} HashTable;

HashTable *hash_table_init(size_t initial_capacity);
void       hash_table_fini(HashTable *h);

int        hash_table_put(HashTable *h, uint64_t key, int value);
/* returns:
 *   1 if inserted new key
 *   0 if updated existing key
 *  -1 on allocation/error
 */

int        hash_table_get(const HashTable *h, uint64_t key, int *out_value);
/* returns 1 if found else 0 */

int        hash_table_delete(HashTable *h, uint64_t key);
/* returns 1 if deleted else 0 */

size_t     hash_table_count(const HashTable *h);

#endif
