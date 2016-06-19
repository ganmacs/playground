#ifndef HASHTAB_H
#define HASHTAB_H

#include <string.h>
#include <stdlib.h>

typedef struct hashtab_node_t {
  void *key;
  void *value;

  size_t key_size;
  size_t value_size;
  struct hashtab_node_t *next;
} hashtab_node_t;

typedef struct hashtab_t {
  hashtab_node_t **tbl;
  size_t size;
} hashtab_t;

hashtab_t *ht_init(size_t size);

void *ht_insert(hashtab_t *hash, void *key, size_t key_size, void* value, size_t value_size);
void *ht_search(hashtab_t *hash, void *key, size_t key_size);

#endif
