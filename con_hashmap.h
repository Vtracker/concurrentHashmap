#pragma once
#include "entry.h"
#include<pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define INIT_SIZE 4

typedef struct con_hashmap
{
    size_t cap;
    size_t load;
    size_t size;
    entry **data;
    size_t hash_offset;
    uint32_t (*hash_func)(void *v);
    bool (*equals)(void* a, void* b);
    pthread_spinlock_t lock;

}con_hashmap;

con_hashmap* creat_con_hashmap(uint32_t (*hash_func)(void* v),bool (*equals)(void* a, void* b))
{
    con_hashmap *ret = (con_hashmap*)malloc(sizeof(con_hashmap));
    ret->cap = (1 << INIT_SIZE);
    ret->load = ret->size = ret->hash_offset = 0;
    ret->data = (entry**)malloc(sizeof(entry *) * (1 << INIT_SIZE));
    entry *heads = create_entries(1 << INIT_SIZE);
    for (int i = 0; i < 1 << INIT_SIZE;i++)
    {
        ret->data[i] = &heads[i];
    }
    ret->hash_func = hash_func;
    ret->equals = equals;
    pthread_spin_init(&ret->lock, PTHREAD_PROCESS_PRIVATE);
    return ret;
}
