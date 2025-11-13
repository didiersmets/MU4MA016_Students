#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

// data structure
struct string_node {
    char *str;           // the string data
    struct avl_node node;  // embedded AVL node
};

// Compare function for strings
static int string_compare(const void *a, const void *b) {
    const struct string_node *node_a = a;
    const struct string_node *node_b = b;
    return strcmp(node_a->str, node_b->str);
}

// Helper to create a new string_node
static struct string_node *create_string_node(const char *str) {
    struct string_node *node = malloc(sizeof(struct string_node));
    if (!node) return NULL;
    
    node->str = strdup(str);  // duplicate the string
    if (!node->str) {
        free(node);
        return NULL;
    }
    
    return node;
}

int main(void) {
    struct avl_tree tree;
    // Calculate offset of avl_node within string_node
    size_t offset = (size_t)&((struct string_node *)0)->node;
    
    // Initialize tree
    avl_tree_initialize(&tree, string_compare, offset);
    
    // Insert some strings
    const char *strings[] = {
        "banana",
        "apple",
        "cherry",
        "date",
        "elderberry"
    };
    
    printf("Inserting strings:\n");
    for (size_t i = 0; i < sizeof(strings)/sizeof(strings[0]); i++) {
        struct string_node *node = create_string_node(strings[i]);
        if (!node) {
            fprintf(stderr, "Failed to create node for %s\n", strings[i]);
            continue;
        }
        printf("  %s\n", strings[i]);
        avl_tree_insert(&tree, node);
    }
    
    // Try to find some strings
    printf("\nLooking up strings:\n");
    const char *lookups[] = {"apple", "banana", "missing", "cherry"};
    
    for (size_t i = 0; i < sizeof(lookups)/sizeof(lookups[0]); i++) {
        // Create a temporary node for comparison
        struct string_node temp = { .str = (char *)lookups[i] };
        struct string_node *found = avl_tree_find(&tree, &temp);
        
        if (found) {
            printf("  Found: %s\n", found->str);
        } else {
            printf("  Not found: %s\n", lookups[i]);
        }
    }

    return 0;
}