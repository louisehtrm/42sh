#include <stdio.h>

#include "hash_map.h"

void hash_map_dump(struct hash_map *hash)
{
    struct pair_list **data = hash->data;
    for (size_t i = 0; i < hash->size; i++)
    {
        struct pair_list *l = data[i];
        while (l && l->next)
        {
            printf("%s", l->key);
            l = l->next;
        }
        if (l)
        {
            printf("%s", l->key);
            printf("\n");
        }
    }
}
