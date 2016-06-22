#ifndef HASHTAB_H
#define HASHTAB_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

typedef struct hashtab_iter_t {
  void* value;
  size_t value_size;
  void* key;
  size_t key_size;

  struct hashtab_intenal_t {
    hashtab_t *hashtbl;
    hashtab_node_t *node;
    int index;
  } internal;

} hashtab_iter_t;


hashtab_t *ht_init(size_t size, int (*ht_hash) (void *, size_t, size_t));

void *ht_insert(hashtab_t *hash, void *key, size_t key_size, void* value, size_t value_size);

void *ht_search(hashtab_t *hash, void *key, size_t key_size);

void ht_destroy(hashtab_t *hash);

void ht_new_iter(hashtab_t *hash, hashtab_iter_t *iter);

void ht_iter_inc(hashtab_iter_t *iter);

void ht_remove(hashtab_t *hash, void *key, size_t key_size);

void *ht_grow(hashtab_t *old_hash, size_t new_size);

void ht_visualize(hashtab_t *hash);
#endif
