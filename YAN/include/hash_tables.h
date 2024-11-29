#ifndef _HASH_TABLES_H
#define _HASH_TABLES_H

#include <stddef.h>

// Implementation of a dictionnary of (key,value) using
// a hash table based on open addressing.
// Genericity for key and value types is obtained by type
// erasure and use of memcmp and memcpy. Keys and values
// must therefore be of fixed length.

typedef struct HashTable {
	unsigned capacity; // Nbr of slots in the table
	unsigned size; // Nbr of occupied slots
	unsigned key_len; // Size in bytes of each key
	unsigned val_len; // Size in bytes of each value
	void *data;
}HashTable ;

HashTable *hash_table_init(size_t capacity, size_t key_len,
				  size_t val_len);

void *hash_table_find(const HashTable *ht, void *key);

void hash_table_insert(HashTable *ht, void *key, void *val);

void hash_table_delete(const HashTable *ht, void *key);

void hash_table_fini(HashTable *ht);

#endif
