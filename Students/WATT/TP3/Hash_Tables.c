#include "Hash_tables.h"

#include <stdlib.h>
#include <string.h>

/* utilities */

static uint64_t splitmix64(uint64_t x) {
    /* Good-quality 64-bit mixing (public domain style). */
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    x = x ^ (x >> 31);
    return x;
}

static size_t next_pow2(size_t x) {
    if (x < 8) return 8;
    x--;
    for (size_t i = 1; i < sizeof(size_t) * 8; i <<= 1) x |= x >> i;
    return x + 1;
}

static int should_grow(const HashTable *h) {
    /* grow when (filled + tombstones) exceeds ~70% */
    size_t used = h->size + h->tombstones;
    return (used * 10) >= (h->cap * 7);
}

/* -------------------- core probing -------------------- */

static size_t index_for(const HashTable *h, uint64_t key) {
    return (size_t)(splitmix64(key) & (uint64_t)(h->cap - 1));
}

static int rehash_into(HashTable *dst, uint64_t key, int value) {
    size_t idx = index_for(dst, key);

    for (;;) {
        if (dst->states[idx] != 1) {
            dst->states[idx] = 1;
            dst->keys[idx] = key;
            dst->values[idx] = value;
            dst->size++;
            return 0;
        }
        idx = (idx + 1) & (dst->cap - 1);
    }
}

static int hash_table_grow(HashTable *h, size_t new_cap) {
    HashTable nh;
    nh.cap = next_pow2(new_cap);
    nh.size = 0;
    nh.tombstones = 0;

    nh.keys = (uint64_t *)malloc(nh.cap * sizeof(uint64_t));
    nh.values = (int *)malloc(nh.cap * sizeof(int));
    nh.states = (uint8_t *)malloc(nh.cap * sizeof(uint8_t));

    if (!nh.keys || !nh.values || !nh.states) {
        free(nh.keys);
        free(nh.values);
        free(nh.states);
        return -1;
    }

    memset(nh.states, 0, nh.cap * sizeof(uint8_t));

    /* re-insert all FILLED slots */
    for (size_t i = 0; i < h->cap; i++) {
        if (h->states[i] == 1) {
            (void)rehash_into(&nh, h->keys[i], h->values[i]);
        }
    }

    free(h->keys);
    free(h->values);
    free(h->states);

    *h = nh;
    return 0;
}

/* -------------------- public API -------------------- */

HashTable *hash_table_init(size_t initial_capacity) {
    HashTable *h = (HashTable *)calloc(1, sizeof(HashTable));
    if (!h) return NULL;

    h->cap = next_pow2(initial_capacity);
    h->size = 0;
    h->tombstones = 0;

    h->keys = (uint64_t *)malloc(h->cap * sizeof(uint64_t));
    h->values = (int *)malloc(h->cap * sizeof(int));
    h->states = (uint8_t *)malloc(h->cap * sizeof(uint8_t));

    if (!h->keys || !h->values || !h->states) {
        hash_table_fini(h);
        return NULL;
    }

    memset(h->states, 0, h->cap * sizeof(uint8_t));
    return h;
}

void hash_table_fini(HashTable *h) {
    if (!h) return;
    free(h->keys);
    free(h->values);
    free(h->states);
    free(h);
}

size_t hash_table_count(const HashTable *h) {
    return h ? h->size : 0;
}

int hash_table_get(const HashTable *h, uint64_t key, int *out_value) {
    if (!h) return 0;

    size_t idx = index_for(h, key);
    for (;;) {
        uint8_t st = h->states[idx];

        if (st == 0) {
            /* empty => key not present and probe chain ends */
            return 0;
        }
        if (st == 1 && h->keys[idx] == key) {
            if (out_value) *out_value = h->values[idx];
            return 1;
        }

        idx = (idx + 1) & (h->cap - 1);
    }
}

int hash_table_put(HashTable *h, uint64_t key, int value) {
    if (!h) return -1;

    if (should_grow(h)) {
        if (hash_table_grow(h, h->cap * 2) != 0) return -1;
    }

    size_t idx = index_for(h, key);
    size_t first_tombstone = (size_t)(-1);

    for (;;) {
        uint8_t st = h->states[idx];

        if (st == 0) {
            /* empty slot: insert here OR into earlier tombstone */
            size_t ins = (first_tombstone != (size_t)(-1)) ? first_tombstone : idx;

            if (h->states[ins] == 2) {
                /* reusing tombstone */
                h->tombstones--;
            }

            h->states[ins] = 1;
            h->keys[ins] = key;
            h->values[ins] = value;
            h->size++;
            return 1;
        }

        if (st == 1) {
            if (h->keys[idx] == key) {
                /* overwrite existing */
                h->values[idx] = value;
                return 0;
            }
        } else if (st == 2) {
            /* remember first tombstone to reuse */
            if (first_tombstone == (size_t)(-1)) first_tombstone = idx;
        }

        idx = (idx + 1) & (h->cap - 1);
    }
}

int hash_table_delete(HashTable *h, uint64_t key) {
    if (!h) return 0;

    size_t idx = index_for(h, key);
    for (;;) {
        uint8_t st = h->states[idx];

        if (st == 0) return 0; /* not found */
        if (st == 1 && h->keys[idx] == key) {
            h->states[idx] = 2; /* tombstone */
            h->size--;
            h->tombstones++;
            return 1;
        }

        idx = (idx + 1) & (h->cap - 1);
    }
}
