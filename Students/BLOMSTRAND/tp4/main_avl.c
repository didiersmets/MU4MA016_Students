#include "avl_tree.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct user_data
{
    const char *s;
    struct avl_node node;
};

static int cmp_user_data(const void *a, const void *b)
{
    const struct user_data *ua = (const struct user_data *)a;
    const struct user_data *ub = (const struct user_data *)b;
    return strcmp(ua->s, ub->s);
}

int main(void)
{
    struct avl_tree t;
    avl_tree_initialize(&t, cmp_user_data, (int)offsetof(struct user_data, node));

    struct user_data x = {.s = "banana"};
    struct user_data y = {.s = "apple"};
    struct user_data z = {.s = "cherry"};

    avl_tree_insert(&t, &x);
    avl_tree_insert(&t, &y);
    avl_tree_insert(&t, &z);

    struct user_data key = {.s = "apple"};
    struct user_data *found = (struct user_data *)avl_tree_find(&t, &key);

    if (found)
        printf("found: %s\n", found->s);
    else
        printf("not found\n");

    return 0;
}
