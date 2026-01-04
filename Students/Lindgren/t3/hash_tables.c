#include "hash_tables.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define FREE_SLOT 0
#define OCCUPIED_SLOT 1
#define DELETED_SLOT 2

struct HashTable *hash_table_init(size_t capacity, size_t key_len,
				  size_t val_len)
{
	struct HashTable *ht = malloc(sizeof(struct HashTable));
	if (!ht)
		return ht;
	ht->key_len = key_len;
	ht->val_len = val_len;
	ht->size = 0;
	unsigned slot_len = 1 + key_len + val_len;
	ht->data = malloc(capacity * slot_len);
	ht->capacity = ht->data ? capacity : 0;
	for (unsigned i = 0; i < ht->capacity; i++) {
		unsigned char *p = (unsigned char *)ht->data + i * slot_len;
		p[0] = FREE_SLOT;
	}
	return ht;
}

/* A general purpose hash function : FNV-1a 32 bits. Cfr :
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 */
uint32_t hash_key(void *key, unsigned key_len)
{
	unsigned char *byte = key;
	uint32_t hash = 2166136261;
	while (key_len--) {
		hash ^= *byte++;
		hash *= 16777619;
	}
	return hash;
}

void *hash_table_find(const struct HashTable *ht, void *key)
{
	if (!ht || !ht->capacity)
		return NULL;
	uint32_t pos = hash_key(key, ht->key_len);
	unsigned slot_len = 1 + ht->key_len + ht->val_len;
	unsigned char *data = ht->data;
	for (size_t probe = 0; probe < ht->capacity; probe++) {
		pos = pos % ht->capacity;
		unsigned char *p = data + pos * slot_len;
		if (p[0] == FREE_SLOT) {
			return NULL;
		}
		if ((p[0] != DELETED_SLOT) &&
		    memcmp(key, p + 1, ht->key_len) == 0) {
			return p + 1 + ht->key_len;
		} else {
			pos++;
		}
	}
	return NULL;
}

static void hash_table_grow(struct HashTable *ht, size_t new_cap);


void hash_table_insert(struct HashTable *ht, void *key, void *val)
{
	if (ht->size >= 2 * ht->capacity / 3) {
		size_t new_cap = ht->capacity < 4 ? 8 : 2 * ht->capacity;
		hash_table_grow(ht, new_cap);
	}
	uint32_t pos = hash_key(key, ht->key_len);
	unsigned slot_len = 1 + ht->key_len + ht->val_len;
	unsigned char *data = ht->data;
	for (size_t probe = 0; probe < ht->capacity; probe++) {
		pos = pos % ht->capacity;
		unsigned char *p = data + pos * slot_len;
		if (p[0] == FREE_SLOT) {
			memcpy(p + 1, key, ht->key_len);
			memcpy(p + 1 + ht->key_len, val, ht->val_len);
			ht->size++;
			p[0] = OCCUPIED_SLOT;
			return;
		} else {
			pos++;
		}
	}
	printf("Hash table is full ! Implement hash_table_grow "
	       "or initialize with a larger capacity.\n");
	abort();
}

static void hash_table_grow(struct HashTable *ht, size_t new_cap)
{
    void *old_data = ht->data;
    unsigned old_capacity = ht->capacity;
    unsigned old_key_len = ht->key_len;
    unsigned old_val_len = ht->val_len;
    unsigned old_slot_len = 1 + old_key_len + old_val_len;

    
    unsigned new_slot_len = 1 + ht->key_len + ht->val_len;
    ht->data = malloc(new_cap * new_slot_len);
    if (!ht->data) {
        
        ht->data = old_data;
        return;
    }

    ht->capacity = (unsigned)new_cap;
    ht->size = 0;


    for (unsigned i = 0; i < ht->capacity; ++i) {
        unsigned char *p =
            (unsigned char *)ht->data + i * new_slot_len;
        p[0] = FREE_SLOT;
    }

    
    for (unsigned i = 0; i < old_capacity; ++i) {
        unsigned char *p =
            (unsigned char *)old_data + i * old_slot_len;
        if (p[0] == OCCUPIED_SLOT) {
            void *key = p + 1;
            void *val = p + 1 + old_key_len;
            hash_table_insert(ht, key, val);
        }
    }

    free(old_data);
}


void hash_table_delete(const struct HashTable *ht_const, void *key)
{    
    struct HashTable *ht = (struct HashTable *)ht_const;

    if (!ht || !ht->capacity) return;

    uint32_t pos = hash_key(key, ht->key_len);
    unsigned slot_len = 1 + ht->key_len + ht->val_len;
    unsigned char *data = ht->data;

    for (size_t probe = 0; probe < ht->capacity; probe++) {
        pos = pos % ht->capacity;
        unsigned char *p = data + pos * slot_len;

        if (p[0] == FREE_SLOT) {
            return;
        }

        if (p[0] == OCCUPIED_SLOT &&
            memcmp(key, p + 1, ht->key_len) == 0) {
            p[0] = DELETED_SLOT;
            if (ht->size > 0) ht->size--;
            return;
        }

        pos++;
    }
}


void hash_table_fini(struct HashTable *ht)
{
	ht->size = 0;
	ht->capacity = 0;
	free(ht->data);
}

#undef FREE_SLOT
#undef OCCUPIED_SLOT
#undef DELETED_SLOT

