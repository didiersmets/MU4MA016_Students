#include "priority_queue.h"
#include "avl_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

static void test_priority_queue(void) {
    printf("=== Priority Queue test ===\n");

    struct priority_queue q;
    if (priority_queue_init(&q, 100) != 0) {
        fprintf(stderr, "priority_queue_init failed\n");
        exit(1);
    }

    priority_queue_push(&q, 10, 5.0f);
    priority_queue_push(&q, 7,  2.0f);
    priority_queue_push(&q, 3,  8.0f);
    priority_queue_push(&q, 42, 1.0f);

    priority_queue_update(&q, 10, 0.5f);

    while (!priority_queue_empty(&q)) {
        struct priority_data x = priority_queue_pop(&q);
        printf("pop: id=%d val=%.3f\n", x.id, x.val);
    }

    priority_queue_destroy(&q);
    printf("\n");
}

struct string_item {
    char *s;
    struct avl_node node; 
};

static int cmp_string_item(const void *a, const void *b) {
    const struct string_item *ia = (const struct string_item *)a;
    const struct string_item *ib = (const struct string_item *)b;
    return strcmp(ia->s, ib->s);
}

static struct string_item *make_item(const char *s) {
    struct string_item *it = (struct string_item *)malloc(sizeof(*it));
    if (!it) exit(1);

    it->s = strdup(s);
    if (!it->s) exit(1);

    it->node.left = NULL;
    it->node.right = NULL;
    it->node.height = 1;
    return it;
}

static void free_item(struct string_item *it) {
    if (!it) return;
    free(it->s);
    free(it);
}

static void test_avl_tree(void) {
    printf("=== AVL Tree test ===\n");

    struct avl_tree t;
    avl_tree_initialize(&t, cmp_string_item, (int)offsetof(struct string_item, node));

    struct string_item *items[] = {
        make_item("pear"),
        make_item("apple"),
        make_item("banana"),
        make_item("orange"),
        make_item("grape")
    };

    for (size_t i = 0; i < sizeof(items)/sizeof(items[0]); ++i) {
        avl_tree_insert(&t, items[i]);
    }

    struct string_item key;
    key.s = "banana";

    struct string_item *found = (struct string_item *)avl_tree_find(&t, &key);
    if (found) printf("found: %s\n", found->s);
    else       printf("not found\n");

    /* no delete required for assignment; free allocated items */
    for (size_t i = 0; i < sizeof(items)/sizeof(items[0]); ++i) {
        free_item(items[i]);
    }

    printf("\n");
}

int main(void) {
    test_priority_queue();
    test_avl_tree();
    return 0;
}
