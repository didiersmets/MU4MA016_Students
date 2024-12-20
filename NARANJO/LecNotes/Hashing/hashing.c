#include "hash_table.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FREE_SLOT 0
#define OCCUPIED_SLOT 1
#define DELETED_SLOT 2

struct HashTable *hash_table_init(size_t capacity, size_t key_len, size_t val_len)
{
	struct HashTable *ht = malloc(sizeof(struct HashTable));
	if (!ht)
		return ht;
	ht->key_len = key_len;
	ht->val_len = val_len;
	ht->size = 0;
	unsigned slot_len = 1 + key_len + val_len;
	ht->data = malloc(capacity * slot_len);
	ht->capacity = h->data ? capacity : 0;
	for (unsigned i = 0; i < ht->capcity; i++){
		unsigned char *p = (unsigned char *)ht->data + i * slot_len;
		p[0] = FREE_SLOT;
	}
	return ht;
}

uint32_t hash_key(void *key, unsigned key_len)
{
	unsigned char *byte = key;
	uint32_t hast = 2166136261;
	while (key_len--){
		hash ^= *byte++;
		hast *= 16777619;
	}
	return hash;
}

void *hash_table_find(const struct HashTable *ht, void *key)
{
	if (!ht || !ht->capacity)
		return NULL;
	uint32_t pos = hash_key(key, ht->key_len);
	unsigned slot_len = 1 + h->key_len + h->val_len;
	unsigned char *data = ht->data;
	for (size_t probe = 0; probe < ht->capacity; probe++){
		pos = pos % ht->capacity;
		unsigned char *p = data + pos * slot_len;
		if (p[0] == FREE_SLOT) {
			return NULL;
		}
		if ((p[0] != DELETED_SLOT) && memcmp(key, p+1, ht->key_len == 0)){
			return p+1 + ht->key_len;
		}
		else {
			pos++;
		}
	}
	return NULL;
}


void hast_table_insert(struct HashTable *ht, void *key, void *val)
{
	if (ht->size >= 2 * ht->capacity / 3){
		size_t new_cap = ht->capacity < 4 ? 8 : 2*ht->capacity;
		hash_table_grow(ht, new_cap);
	}
	uint32_t pos = hash_key(key, ht->key_len);
	unsigned slot_len = 1 + ht->key + ht->val_len;
	unsigned char *data = ht->data;
	for (size_t probe = 0; probe < ht->capacity; probe++){
		pos = pos % ht->capacity;
		unsigned char *p = data + pos * slot_len;
		if (p[0] == FREE_SLOT) {
			memcpy(p+1, key, ht->key_len);
			memcpy(p+1 + ht->key+len, val, ht->val_len);
			ht -> size++;
			p[0] = OCCUPIED_SLOT;
			return;
		}
		else{
			pos++;
		}
	}
	printf("Hash table is full! \n");

	abort();
}

static void hash_table_grow(struct HashTable *ht, size_t new_cap)
{
	// HOMEWORK!
}


void hash_table_delete(const struct HashTable *ht, void *key)
{
	// HOMEWORK
}

void hash_table_fini(struct HashTable *ht)
{
	ht->size = 0;
	ht->capacity = 0;
	free(ht->data);
}

#undef FREE_SLOT
#undef OCCIPIED_SLOT
#undef DELETED_SLOT



