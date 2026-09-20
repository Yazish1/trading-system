#ifndef HASH_H
#define HASH_H
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 256

struct hashNode
{
    uint64_t key;
    void *data;
    struct hashNode *next;
};

struct HashMap
{
    struct hashNode **buckets;
    size_t size;
    size_t count;
};

int hash_function(uint64_t key)
{
    return key % ARRAY_SIZE;
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

void hashmap_insert(struct HashMap *map, uint64_t key, void *data)
{
    int index = hash_function(key);
    struct hashNode *node = (struct hashNode *)malloc(sizeof(*node));
    if (node == NULL)
    {
        perror("Failed to allocate node memory");
        return;
    }
    node->key = key;
    node->data = data;
    node->next = NULL;
    add_to_ll(map, index, node);
}

struct hashNode *hashmap_find(struct HashMap *map, uint64_t key)
{
    int index = hash_function(key);
    struct hashNode *curr = map->buckets[index];
    while (curr != NULL)
    {
        if (curr->key == key)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void hashmap_delete(struct HashMap *map, uint64_t key)
{
    int index = hash_function(key);
    if (map->buckets[index] == NULL)
    {
        return;
    }
    struct hashNode *curr = map->buckets[index];
    if (curr->key == key)
    {
        map->buckets[index] = curr->next;
        free(curr);
        return;
    }
    struct hashNode *prev = NULL;
    while (curr != NULL)
    {
        if (curr->key == key)
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
#endif