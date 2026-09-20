#include <hashmap.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 256

int hash_function(uint64_t order_id)
{
    return order_id % ARRAY_SIZE;
}

void add_to_ll(struct HashMap *map, int index, struct hashNode *node)
{
    struct hashNode *curr = map->buckets[index];
    if (curr == NULL)
    {
        map->buckets[index] = node;
        return;
    }
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = node;
    map->count++;
}

struct HashMap *hashmap_create(size_t numBuckets)
{
    struct HashMap *map = (struct HashMap *)malloc(sizeof(*map));
    if (map == NULL)
    {
        perror("Failed to allocate map memory");
        return;
    }
    map->buckets = (struct hashNode **)calloc(numBuckets, sizeof(struct hashNode *));
    if (map->buckets == NULL)
    {
        perror("Failed to allocate buckets memory");
        return;
    }
    map->size = numBuckets;
    map->count = 0;
    return map;
}

void hashmap_insert(struct HashMap *map, uint64_t order_id, struct details_of_order *data)
{
    int index = hash_function(order_id);
    struct hashNode *node = (struct hashNode *)malloc(sizeof(*node));
    if (node == NULL)
    {
        perror("Failed to allocate node memory");
        return;
    }
    node->order_id = order_id;
    node->data = data;
    node->next = NULL;
    add_to_ll(map, index, node);
}

struct hashNode *hashmap_find(struct HashMap *map, uint64_t order_id)
{
    int index = hash_function(order_id);
    struct hashNode *curr = map->buckets[index];
    while (curr != NULL)
    {
        if (curr->order_id == order_id)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void hashmap_delete(struct HashMap *map, uint64_t order_id)
{
    int index = hash_function(order_id);
    if (map->buckets[index] == NULL)
    {
        return;
    }
    struct hashNode *curr = map->buckets[index];
    if (curr->order_id == order_id)
    {
        map->buckets[index] = curr->next;
        free(curr);
        return;
    }
    struct hashNode *prev = NULL;
    while (curr != NULL)
    {
        if (curr->order_id == order_id)
        {
            struct hashNode *nxt = curr->next;
            prev->next = curr->next;
            free(curr);
            curr = nxt;
            map->count--;
            continue;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}
