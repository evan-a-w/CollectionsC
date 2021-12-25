#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LOAD 0.75
#define DEFAULT_CAPACITY 10
#define TABLE_REALLOC_FACTOR 4
#define MAX_LONG_STRING_LENGTH 21

// from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(const char *str);

unsigned long hash2(const char *str, unsigned long cap);

typedef struct KvPair {
    char *key;
    void *val;
} *kv_pair_t;

void *kv_pair_delete(kv_pair_t p);

typedef struct HashTable {
    unsigned long size;
    unsigned long capacity;
    kv_pair_t *boxes;
} *hash_table_t;

bool is_prime(unsigned long x);

unsigned long nearest_prime(unsigned long x);

void hash_table_realloc(hash_table_t table);

void *hash_table_add(hash_table_t table, const char *key, void *val);

hash_table_t hash_table_new();

void hash_table_free(hash_table_t table);

void hash_table_add_long(hash_table_t table, long x, void *val);

void *hash_table_remove_long(hash_table_t table, long x);

void *hash_table_find(hash_table_t table, const char *key);

void *hash_table_find_long(hash_table_t table, long x);

void *hash_table_remove(hash_table_t table, const char *key);

#endif // HASH_TABLE_H
