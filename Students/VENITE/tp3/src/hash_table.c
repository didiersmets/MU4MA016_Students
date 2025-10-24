#include "../include/hash_table.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction de hachage simple pour une arête
static size_t hash_edge(Edge key, size_t size) {
    // Une fonction de hachage simple mais efficace pour une paire d'entiers
    size_t hash = 17;
    hash = hash * 31 + key.v1;
    hash = hash * 31 + key.v2;
    return hash % size;
}

HashTable* ht_create(size_t size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) return NULL;
    ht->size = size;
    ht->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    return ht;
}

void ht_dispose(HashTable* ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->size; ++i) {
        HashNode* current = ht->buckets[i];
        while (current) {
            HashNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

void ht_insert(HashTable* ht, Edge key, int value) {
    size_t index = hash_edge(key, ht->size);
    
    // Crée un nouveau nœud
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (!new_node) {
        fprintf(stderr, "Erreur d'allocation pour le noeud de hachage.\n");
        return;
    }
    new_node->key = key;
    new_node->value = value;
    
    // Insère en tête de la liste chaînée
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
}

int ht_find(const HashTable* ht, Edge key) {
    size_t index = hash_edge(key, ht->size);
    HashNode* current = ht->buckets[index];
    while (current) {
        if (current->key.v1 == key.v1 && current->key.v2 == key.v2) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Non trouvé
}
