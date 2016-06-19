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

void
ht_destroy(hashtab_t *hash)
{
  hashtab_node_t *last_node, *next_node;

  for (int i = 0; i < (int)hash->size; i++) {
    next_node = hash->tbl[i];
    while (next_node != NULL) {
      free(next_node->value);
      free(next_node->key);
      last_node = next_node;
      next_node = next_node->next;
      free(last_node);
    }
  }

  free(hash->tbl);
  free(hash);
}

void
ht_new_iter(hashtab_t *hash, hashtab_iter_t *iter)
{
  iter->internal.hashtbl = hash;
  iter->internal.node = NULL;
  iter->internal.index = - 1;

  ht_iter_inc(iter);
}

void ht_iter_inc(hashtab_iter_t *iter)
{
  hashtab_t *hashtbl = iter->internal.hashtbl;
  int index = iter->internal.index;

  if (iter->internal.node == NULL || iter->internal.node->next == NULL) {
    index++;
  } else {
    iter->internal.node = iter->internal.node->next;

    iter->key = iter->internal.node->key;
    iter->value = iter->internal.node->value;
    iter->key_size = iter->internal.node->key_size;
    iter->value_size = iter->internal.node->value_size;

    return;
  }

  while (hashtbl->tbl[index] == NULL && index < (int)hashtbl->size) index++;

  if (index >= (int)hashtbl->size) {
    iter->internal.node = NULL;
    iter->internal.index = hashtbl->size;

    iter->key = NULL;
    iter->value = NULL;
    iter->key_size = 0;
    iter->value_size = 0;
    return;
  }

  iter->internal.node = hashtbl->tbl[index];
  iter->internal.index = index;

  iter->key = iter->internal.node->key;
  iter->value = iter->internal.node->value;
  iter->key_size = iter->internal.node->key_size;
  iter->value_size = iter->internal.node->value_size;
}

void
ht_remove(hashtab_t *hash, void *key, size_t key_size)
{
  int bin = ht_hash(key, key_size, hash->size);
  hashtab_node_t *next_node = hash->tbl[bin];
  hashtab_node_t *last_node = NULL;

  if (next_node == NULL) return;

  while (next_node != NULL) {
    if (next_node->key_size == key_size && memcmp(next_node->key, key, key_size) == 0) {
      free(next_node->value);
      free(next_node->key);

      if (last_node != NULL) {  /* first element of list or not */
        last_node->next = next_node->next;
      } else {
        hash->tbl[bin] = next_node->next;
      }

      free(next_node);
      return;
    }

    last_node = next_node;
    next_node = next_node->next;
  }
}

void *
ht_grow(hashtab_t *old_hash, size_t new_size)
{
  hashtab_t *new_hash = ht_init(new_size);
  if (new_hash == NULL) return NULL;

  void *ret;

  hashtab_iter_t iter;
  ht_new_iter(new_hash, &iter);

  for (; iter.key != NULL; ht_iter_inc(&iter)) {
    if ((ret = ht_insert(new_hash, iter.key, iter.key_size, iter.value, iter.value_size)) == NULL) {
      ht_destroy(new_hash);
      return NULL;
    }
  }

  ht_destroy(old_hash);
  return new_hash;
}
