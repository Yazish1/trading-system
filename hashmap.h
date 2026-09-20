#ifndef HASH_H
#define HASH_H

#define ARRAY_SIZE 256

enum heapSide
{
    HEAP_BID,
    HEAP_ASK
};
struct details_of_order
{
    enum heapSide;
    size_t heap_index;
};
struct hashNode
{
    uint64_t order_id;
    struct details_of_order *data;
    struct hashNode *next;
};
struct HashMap
{
    struct hashNode **buckets;
    size_t size;
    size_t count;
};

int hash_function(uint64_t order_id);
void add_to_ll(struct HashMap *map, int index, struct hashNode *node);
struct HashMap *hashmap_create(size_t numBuckets);
void hashmap_insert(struct HashMap *map, uint64_t order_id, struct details_of_order *data);
struct hashNode *hashmap_find(struct HashMap *map, uint64_t order_id);
void hashmap_delete(struct HashMap *map, uint64_t order_id);
#endif