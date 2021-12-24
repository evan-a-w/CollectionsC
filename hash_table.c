#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LOAD 0.7
#define DEFAULT_CAPACITY 10
#define TABLE_REALLOC_FACTOR 4
#define MAX_LONG_STRING_LENGTH 21

// from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

unsigned long hash2(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 2) + hash) + c; /* hash * 5 + c */

    return hash;
}

typedef struct KvPair {
    char *key;
    void *val;
} *kv_pair_t;

void *kv_pair_delete(kv_pair_t p) {
    free(p->key);
    void *val = p->val;
    free(p);
    return val;
}

typedef struct HashTable {
    unsigned long size;
    unsigned long capacity;
    kv_pair_t *boxes;
} *hash_table_t;

// Can be MUCH better - dont wanna -lm for sqrt
bool is_prime(unsigned long x) {
    for (unsigned long i = 2; i < x; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

unsigned long nearest_prime(unsigned long x) {
    unsigned long res;
    for (res = x; ; res++) {
        if (is_prime(res))
            break;
    }
    return res;
}

void hash_table_realloc(hash_table_t table) {
    unsigned long new_capacity = nearest_prime(table->capacity * TABLE_REALLOC_FACTOR);
    fprintf(stderr, "Allocating with new cap %lu\n", new_capacity);
    kv_pair_t *new_boxes = calloc(new_capacity, sizeof(kv_pair_t));
    bool *visited = malloc(table->capacity * sizeof(bool));
    for (unsigned long i = 0; i < table->capacity; i++) {
        if (table->boxes[i] != NULL) {
            char *key = table->boxes[i]->key;
            unsigned long hashed = hash(key);
            unsigned long inc = hash2(key);
            unsigned long index = hashed % new_capacity;
            int j;
            for (j = index; new_boxes[j]; j = (j + inc) % new_capacity)
                ;
            new_boxes[j] = table->boxes[i];
        }
    }
    free(visited);
    free(table->boxes);
    table->boxes = new_boxes;
    table->capacity = new_capacity;
}

// Takes ownership of val (needs to be a valid pointer), but copies key
// Returns old val if present, else NULL.
void *hash_table_add(hash_table_t table, const char *key, void *val) {
    table->size++;
    unsigned long hashed = hash(key);
    unsigned long inc = hash2(key);
    unsigned long index = hashed % table->capacity;
    bool *visited = calloc(table->capacity, sizeof(bool));
    void *res = NULL;
    int i;
    for (i = index; table->boxes[i] && !visited[i]; i = (i + inc) % table->capacity) {
        visited[i] = true;
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
    fprintf(stderr, "load: %lf\n", load);
    if (load > MAX_LOAD)
        hash_table_realloc(table);

    free(visited);
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
    for (unsigned long i = 0; i < table->capacity; i++) {
        if (table->boxes[i] != NULL) {
            free(table->boxes[i]->key);
            free(table->boxes[i]);
        }
    }
    free(table->boxes);
    free(table);
}

void hash_table_add_long(hash_table_t table, long x, void *val) {
    char key[MAX_LONG_STRING_LENGTH];
    snprintf(key, MAX_LONG_STRING_LENGTH, "%ld", x);
    hash_table_add(table, key, val);
}

void *hash_table_find(hash_table_t table, const char *key) {
    unsigned long hashed = hash(key);
    unsigned long inc = hash2(key);
    unsigned long index = hashed % table->capacity;

    bool *visited = calloc(table->capacity, sizeof(bool));

    for (int i = index; !visited[i]; i = (i + inc) % table->capacity) {
        visited[i] = true;
        if (table->boxes[i]) {
            if (strcmp(table->boxes[i]->key, key) == 0) {
                free(visited);
                return table->boxes[i]->val;
            }
        }
    }

    free(visited);
    return NULL;
}

void *hash_table_find_long(hash_table_t table, long x) {
    char key[MAX_LONG_STRING_LENGTH];
    snprintf(key, MAX_LONG_STRING_LENGTH, "%ld", x);
    return hash_table_find(table, key);
}

void *hash_table_remove(hash_table_t table, const char *key) {
    unsigned long hashed = hash(key);
    unsigned long inc = hash2(key);
    unsigned long index = hashed % table->capacity;

    bool *visited = calloc(table->capacity, sizeof(bool));

    for (int i = index; !visited[i]; i = (i + inc) % table->capacity) {
        visited[i] = true;
        if (table->boxes[i]) {
            if (strcmp(table->boxes[i]->key, key) == 0) {
                free(visited);
                kv_pair_t p = table->boxes[i];
                table->boxes[i] = NULL;
                return kv_pair_delete(p);
            }
        }
    }

    free(visited);
    return NULL;
}

int main(void) {
    hash_table_t table = hash_table_new();
    hash_table_add(table, "hello", "world");
    hash_table_add(table, "goodbye", (void*)1);

    printf("%s\n", (char *) hash_table_find(table, "hello"));
    printf("%ld\n", (long) hash_table_find(table, "goodbye"));
    assert(hash_table_find(table, "not there") == NULL);

    hash_table_remove(table, "hello");
    assert(hash_table_find(table, "hello") == NULL);
    hash_table_remove(table, "goodbye");
    assert(hash_table_find(table, "goodbye") == NULL);

    hash_table_free(table);

    table = hash_table_new();

    for (unsigned long i = 0; i < 100; i++) {
        hash_table_add_long(table, i, (void*)i);
        printf("Added %lu\n", i);
    }

    for (int i = 0; i < 100; i++) {
        printf("%lu\n", (unsigned long)hash_table_find_long(table, i));
    }

    printf("%lu\n", (unsigned long)hash_table_find(table, "pener"));

    hash_table_free(table);
}
