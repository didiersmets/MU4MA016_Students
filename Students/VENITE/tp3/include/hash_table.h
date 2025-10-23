#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h> // Pour size_t

typedef struct {
    int v1;
    int v2;
} Edge;


typedef struct HashNode {
    Edge key;
    int value; // L'index du triangle
    struct HashNode* next;
} HashNode;

typedef struct {
    size_t size;
    HashNode** buckets;
} HashTable;


HashTable* ht_create(size_t size);


void ht_dispose(HashTable* ht);


void ht_insert(HashTable* ht, Edge key, int value);


int ht_find(const HashTable* ht, Edge key);

#endif // HASH_TABLE_H
