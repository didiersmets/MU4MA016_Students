#include "AVL_Tree.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h> /* offsetof */

/* User payload */
struct string_item {
    const char *s;
    struct avl_node node; /* embedded intrusive node */
};

/* Compare two string_item by their string (lexicographic order) */
static int string_item_cmp(const void *a, const void *b)
{
    const struct string_item *ia = (const struct string_item *)a;
    const struct string_item *ib = (const struct string_item *)b;
    return strcmp(ia->s, ib->s);
}

/* In-order traversal for demo (prints sorted order) */
static void inorder_print(struct avl_tree *t, struct avl_node *n)
{
    if (!n) return;
    inorder_print(t, n->left);

    struct string_item *it = (struct string_item *)((char *)n - t->offset);
    printf("%s\n", it->s);

    inorder_print(t, n->right);
}

int main(void)
{
    struct avl_tree t;
    avl_tree_initialize(&t, string_item_cmp, (int)offsetof(struct string_item, node));

    struct string_item items[] = {
        {.s = "delta"},
        {.s = "alpha"},
        {.s = "charlie"},
        {.s = "bravo"},
        {.s = "echo"},
        {.s = "bravo"},   /* duplicate: will be ignored */
    };

    int n = (int)(sizeof(items) / sizeof(items[0]));
    for (int i = 0; i < n; i++) {
        avl_tree_insert(&t, &items[i]);
    }

    printf("In-order traversal (sorted):\n");
    inorder_print(&t, t.root);

    struct string_item key = {.s = "charlie"};
    struct string_item *found = (struct string_item *)avl_tree_find(&t, &key);
    printf("\nFind 'charlie': %s\n", found ? found->s : "(not found)");

    struct string_item key2 = {.s = "foxtrot"};
    found = (struct string_item *)avl_tree_find(&t, &key2);
    printf("Find 'foxtrot': %s\n", found ? found->s : "(not found)");

    return 0;
}
