#pragma once
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct entry
{
    void *key;
    void *val;
    struct entry *next;
}entry;

entry* create_entry(void* key,void* val,entry* next)
{
    entry* ret = (entry*)malloc(sizeof(entry));
    ret->key = key;
    ret->val = val;
    ret->next = next;
    return ret;
}

entry* create_entries(int n)
{
    return (entry*)calloc(n,sizeof(entry));
}

void put(entry* head,entry* item,bool (*equals)(void* a, void* b))
{
    while(head->next)
    {
        entry *cur = head->next;
        if(equals(cur->key,item->key))
        {
            cur->val = item->val;
            return;
        }
        head = head->next;
    }
    head->next = item;
    item->next = NULL;
}

void* get(entry* head, void* key, bool (*equals)(void* a, void* b))
{
    void *ret = NULL;
    while(head->next)
    {
        entry *cur = head->next;
        if((*equals)(cur->key, key)) {
            ret = cur->val;
            return cur;
        }
        head = head->next;
    }
    return ret;
}

void* del(entry* head, void* key, bool (*equals)(void* a, void* b))
{
    while(head->next) {
        entry* cur = head->next;
        if((*equals)(cur->key, key)) {
            head->next = cur->next;
            return cur;
        }
        head = head->next;
    }
    return NULL;
}
