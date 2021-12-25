#include "hash_table.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

#define NUM_BENCH 1000000
#define NUM_BENCH_NUMS 10
#define NUM_BENCH_TRIES 3

// from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void *kv_pair_delete(kv_pair_t p) {
    free(p->key);
    void *val = p->val;
    free(p);
    return val;
}

bool is_prime(unsigned long x) {
    unsigned long lim = floor(sqrt(x));
    for (unsigned long i = 2; i <= lim; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

unsigned long nearest_prime(unsigned long x) {
    if (x < 2) return 2;
    unsigned long res;
    for (res = x; ; res++) {
        if (is_prime(res))
            break;
    }
    return res;
}

void hash_table_realloc(hash_table_t table, unsigned long new_capacity) {
    assert(new_capacity >= table->size);
    kv_pair_t *new_boxes = calloc(new_capacity, sizeof(kv_pair_t));
    for (unsigned long i = 0; i < table->capacity; i++) {
        if (table->boxes[i] != NULL) {
            char *key = table->boxes[i]->key;
            unsigned long hashed = hash(key);
            unsigned long index = hashed % new_capacity;
            int j;
            for (j = index; new_boxes[j]; j = (j + 1) % new_capacity)
                ;
            new_boxes[j] = table->boxes[i];
        }
    }
    free(table->boxes);
    table->boxes = new_boxes;
    table->capacity = new_capacity;
}

// Takes ownership of val (needs to be a valid pointer), but copies key
// Returns old val if present, else NULL.
void *hash_table_add(hash_table_t table, const char *key, void *val) {
    table->size++;
    unsigned long hashed = hash(key);
    unsigned long index = hashed % table->capacity;
    void *res = NULL;
    int i;
    for (i = index; table->boxes[i]; i = (i + 1) % table->capacity) {
        if (strcmp(table->boxes[i]->key, key) == 0) {
            res = kv_pair_delete(table->boxes[i]);
            table->size--;
            break;
        }
    }
    table->boxes[i] = malloc(sizeof(struct KvPair));
    table->boxes[i]->key = malloc(strlen(key) + 1);
    strcpy(table->boxes[i]->key, key);
    table->boxes[i]->val = val;

    double load = ((double) table->size) / (double) table->capacity;
    if (load > MAX_LOAD)
        hash_table_realloc(table, nearest_prime(table->capacity * TABLE_REALLOC_FACTOR));

    return res;
}

void *hash_table_add_owned(hash_table_t table, char *key, void *val) {
    table->size++;
    unsigned long hashed = hash(key);
    unsigned long index = hashed % table->capacity;
    void *res = NULL;
    int i;
    for (i = index; table->boxes[i]; i = (i + 1) % table->capacity) {
        if (strcmp(table->boxes[i]->key, key) == 0) {
            res = kv_pair_delete(table->boxes[i]);
            table->size--;
            break;
        }
    }
    table->boxes[i] = malloc(sizeof(struct KvPair));
    table->boxes[i]->key = key;
    table->boxes[i]->val = val;

    double load = ((double) table->size) / (double) table->capacity;
    if (load > MAX_LOAD)
        hash_table_realloc(table, nearest_prime(table->capacity * TABLE_REALLOC_FACTOR));

    return res;
}

hash_table_t hash_table_new() {
    hash_table_t table = malloc(sizeof(struct HashTable));
    table->size = 0;
    table->capacity = nearest_prime(DEFAULT_CAPACITY);
    table->boxes = calloc(table->capacity, sizeof(kv_pair_t));
    return table;
}

void hash_table_free(hash_table_t table) {
    if (table) {
        for (unsigned long i = 0; i < table->capacity; i++) {
            if (table->boxes[i] != NULL) {
                free(table->boxes[i]->key);
                free(table->boxes[i]);
            }
        }
        free(table->boxes);
        free(table);
    }
}

void hash_table_add_long(hash_table_t table, long x, void *val) {
    char key[MAX_LONG_STRING_LENGTH];
    snprintf(key, MAX_LONG_STRING_LENGTH, "%ld", x);
    hash_table_add(table, key, val);
}

void *hash_table_remove_long(hash_table_t table, long x) {
    char key[MAX_LONG_STRING_LENGTH];
    snprintf(key, MAX_LONG_STRING_LENGTH, "%ld", x);
    return hash_table_remove(table, key);
}

kv_pair_t hash_table_find(hash_table_t table, const char *key) {
    unsigned long hashed = hash(key);
    unsigned long index = hashed % table->capacity;


    for (int i = index; table->boxes[i]; i = (i + 1) % table->capacity) {
        if (strcmp(table->boxes[i]->key, key) == 0) {
            return table->boxes[i];
        }
    }

    return NULL;
}

kv_pair_t hash_table_find_long(hash_table_t table, long x) {
    char key[MAX_LONG_STRING_LENGTH];
    snprintf(key, MAX_LONG_STRING_LENGTH, "%ld", x);
    return hash_table_find(table, key);
}

void *hash_table_remove(hash_table_t table, const char *key) {
    int i = hash(key) % table->capacity;
    for (;;) {
        if (table->boxes[i] == NULL)
            return NULL;
        if (strcmp(table->boxes[i]->key, key) == 0)
            break;
        i = (i + 1) % table->capacity;
    }
    void *res = kv_pair_delete(table->boxes[i]);
    table->boxes[i] = NULL;
    table->size--;

    i = (i + 1) % table->capacity;
    while (table->boxes[i]) {
        void *val = table->boxes[i]->val;
        char *tkey = table->boxes[i]->key;
        free(table->boxes[i]);
        table->boxes[i] = NULL;
        table->size--;
        hash_table_add_owned(table, tkey, val);
        i = (i + 1) % table->capacity;
    }

    double load = ((double) table->size) / (double) table->capacity;
    if (load < MIN_LOAD)
        hash_table_realloc(table, nearest_prime(table->size + table->size / 2));

    return res;
}

void hash_table_print_all(hash_table_t table) {
    for (int i = 0; i < table->capacity; i++) {
        if (table->boxes[i] != NULL) {
            printf("%s: %p\n", table->boxes[i]->key, table->boxes[i]->val);
        }
    }
}

void tests() {
    hash_table_t table = hash_table_new();
    hash_table_add(table, "hello", "world");
    hash_table_add(table, "goodbye", (void*)1);

    assert(strcmp(hash_table_find(table, "hello")->val, "world") == 0);
    assert((long) hash_table_find(table, "goodbye")->val == 1);
    assert(hash_table_find(table, "not there") == NULL);

    hash_table_remove(table, "hello");
    assert(hash_table_find(table, "hello") == NULL);
    hash_table_remove(table, "goodbye");
    assert(hash_table_find(table, "goodbye") == NULL);

    hash_table_free(table);

    table = hash_table_new();

    for (unsigned long i = 0; i < 100; i++) {
        hash_table_add_long(table, i, (void*)i);
        assert(table->size == i + 1);
    }

    for (unsigned long i = 0; i < 100; i++) {
        assert((long) hash_table_find_long(table, i)->val == i);
    }

    for (unsigned long i = 0; i < 100; i++) {
        hash_table_remove_long(table, i);
        assert(table->size == 100 - i - 1);
    }

    hash_table_free(table);
}

char *random_string(int len) {
    char *res = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        res[i] = (rand() % (126 - 33)) + 33;
    }
    res[len] = '\0';
    return res;
}

void benchmark() {
    unsigned long times[NUM_BENCH_NUMS][2] = {0};
    int lengths[] = {50, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 1000000};
    struct timeval before, after;
    for (int k = 0; k < NUM_BENCH_TRIES; k++) {
        srand(696969);
        char *strings[NUM_BENCH] = {0};

        for (int i = 0; i < NUM_BENCH; i++)
            strings[i] = random_string(20);

        for (int i = 0; i < NUM_BENCH_NUMS; i++) {
            gettimeofday(&before, NULL);
            hash_table_t table = hash_table_new();

            for (int j = 0; j < lengths[i]; j++)
                hash_table_add(table, strings[j], "data -- oh yeah");

            for (int j = 0; j < lengths[i]; j++)
                assert(hash_table_find(table, strings[j]) != NULL);

            hash_table_free(table);

            gettimeofday(&after, NULL);
            times[i][0] += after.tv_sec - before.tv_sec;
            times[i][1] += after.tv_usec - before.tv_usec;
        }

        for (int i = 0; i < NUM_BENCH; i++)
            free(strings[i]);
    }

    for (int i = 0; i < NUM_BENCH_NUMS; i++)
        printf("%d: %lf %lf\n", lengths[i],
               (double)times[i][0] / (double)NUM_BENCH_TRIES,
               (double)times[i][1] / (double)NUM_BENCH_TRIES);
}
