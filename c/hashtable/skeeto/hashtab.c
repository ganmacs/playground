#include "hashtab.h"

int
ht_hash(void* key, size_t key_size, size_t hash_size)
{
  int v = 0;
  for (int i = 0; i < (int)key_size; i++) {
    v += ((unsigned char *)key)[i] * (i + 1);
  }

  return (v % (int)hash_size);
}

hashtab_t *
ht_init(size_t size)
{
  if ((int)size < 0) return NULL;

  hashtab_t* hash = malloc(sizeof(hashtab_t));

  hash->tbl = malloc(sizeof(hashtab_node_t *) * size);

  hash->size = size;

  for (int i = 0; i < (int) size; i++) {
    hash->tbl[i] = NULL;
  }
  return hash;
}

hashtab_node_t *
new_node(void* value, size_t value_size, void *key, size_t key_size)
{
  hashtab_node_t *n_node = NULL;
  if ((n_node = malloc(sizeof(hashtab_node_t))) == NULL) return NULL;

  n_node->key = malloc(key_size);
  n_node->value = malloc(value_size);

  if (n_node->key == NULL || n_node->value == NULL) {
    free(n_node->key);
    free(n_node->value);
    free(n_node);
    return NULL;
  }

  memcpy(n_node->key, key, key_size);
  memcpy(n_node->value, value, value_size);
  n_node->key_size = key_size;
  n_node->value_size = value_size;
  n_node->next = NULL;

  return n_node;
}

void *
ht_insert(hashtab_t *hash, void *key, size_t key_size, void* value, size_t value_size)
{
  int bin = ht_hash(key, key_size, hash->size);
  hashtab_node_t *next_node = hash->tbl[bin];
  hashtab_node_t *last_node = NULL;

  while (next_node != NULL) {
    if (next_node->key_size != key_size || memcmp(next_node->key, key, key_size) != 0) continue;

    if (next_node->value_size != value_size) {
      free(next_node->value);
      next_node->value = malloc(value_size);
      if (next_node->value == NULL) return NULL;
    }

    last_node = next_node;
    next_node = next_node->next;
  }

  hashtab_node_t *n_node = new_node(value, value_size, key, key_size);
  if (n_node == NULL) return NULL;

  if (last_node == NULL) {
    hash->tbl[bin] = n_node;
  } else {
    last_node->next = n_node;
  }

  return n_node->value;
}

void *
ht_search(hashtab_t *hash, void *key, size_t key_size)
{
  int bin = ht_hash(key, key_size, hash->size);
  hashtab_node_t *node = hash->tbl[bin];

  if (node == NULL) return NULL;

  while (node != NULL) {
    if (node->key_size == key_size && memcmp(node->key, key, key_size) == 0) return node->value;
    node = node->next;
  }

  return NULL;
}
