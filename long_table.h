#ifndef LONG_TABLE_H
#define LONG_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LOAD 0.75
#define DEFAULT_CAPACITY 10
#define TABLE_REALLOC_FACTOR 4
#define MAX_LONG_STRING_LENGTH 21

typedef struct KvLPair {
    unsigned long key;
    void *val;
} *kvl_pair_t;

typedef struct LongTable {
    unsigned long size;
    unsigned long capacity;
    kvl_pair_t *boxes;
} *long_table_t;

unsigned long hashl(unsigned long x);

void *kvl_pair_delete(kvl_pair_t p);

bool is_prime(unsigned long x);

unsigned long nearest_prime(unsigned long x);

void long_table_realloc(long_table_t table);

void *long_table_add(long_table_t table, unsigned long key, void *val);

long_table_t long_table_new();

void long_table_free(long_table_t table);

kvl_pair_t long_table_find(long_table_t table, unsigned long key);

void *long_table_remove(long_table_t table, unsigned long key);

#endif // LONG_TABLE_H
