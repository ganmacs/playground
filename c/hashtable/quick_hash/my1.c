#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define CHAR_SIZE_BIT (sizeof(char) * 8)

struct entry_s {
  char *key;
  char *value;
  struct entry_s *next;
};
typedef struct entry_s entry_t;

struct hashtable_s {
  int size;
  entry_t **table;
};
typedef struct hashtable_s hashtable_t;


hashtable_t *
ht_create(int size)
{
  hashtable_t *hashtable = NULL;
  int i;

  if (size < 1) return NULL;

  if ((hashtable = malloc(sizeof(hashtable_t))) == NULL) {
    return NULL;
  }

  if ((hashtable->table = malloc(sizeof(entry_t *) * size)) == NULL) {
    return NULL;
  }

  for (i = 0; i < size; i++) {
    hashtable->table[i] = NULL;
  }

  hashtable->size = size;

  return hashtable;
}


int
ht_hash(hashtable_t *hashtable, char* key)
{
	unsigned long int hashval; /* TODO check: both initialize version or not */

  printf("-----\n");
  printf("%lu\n", hashval);
  printf("%p\n", &hashval);

  size_t i = 0;

  while (hashval < ULONG_MAX && i < strlen(key)) {
		hashval = hashval << CHAR_SIZE_BIT;
    hashval += key[i];
    i++;
  }

  printf("%lu\n", hashval % hashtable->size);
  puts("-----\n");

  return hashval % hashtable->size;
}

entry_t *
new_entry(char *key, char *value)
{
  entry_t *entry;

  if ((entry = malloc(sizeof(entry_t))) == NULL) {
    return NULL;
  }

  if ((entry->key = strdup(key)) == NULL) {
    return NULL;
  }

  if ((entry->value = strdup(value)) == NULL) {
    return NULL;
  }

  entry->next = NULL;

  return entry;
}

void
ht_set(hashtable_t *hashtable, char *key, char *value)
{
  int bin = 0;
  entry_t *next = NULL;
  entry_t *last = NULL;
  entry_t *newpair = NULL;

  bin = ht_hash(hashtable, key);

  next = hashtable->table[bin];

  while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
    last = next;
    next = last->next;
  }

  /* already existing pair,  replace it */
  if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
    free(next->value);
    next->value = strdup(value);

    /* time to create keypair */
  } else {
    newpair = new_entry(key, value);

    if (next == hashtable->table[bin]) { /* first elem of linked list */
      newpair->next = next;
      hashtable->table[bin] = newpair;

      /* end of the linked list */
    } else if (next == NULL) {
      last->next = newpair;

    } else {
      newpair->next = next;
      last->next = newpair;
    }
  }
}

char*
ht_get(hashtable_t *hashtable, char *key)
{
  int bin = 0;
  entry_t *pair;

  bin = ht_hash(hashtable, key);
  pair = hashtable->table[bin];

  while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
    pair = pair->next;
  }

  if (pair == NULL || pair->key == NULL|| strcmp(key, pair->key) != 0) {
    return NULL;
  } else {
    return pair->value;
  }
}

int
main(int argc, char **argv)
{
  hashtable_t *ht = ht_create(65536);

  ht_set(ht, "key1", "saikou");
  ht_set(ht, "key12", "saikou2");


  printf("%s\n", ht_get(ht, "key1"));
  printf("%s\n", ht_get(ht, "key12"));
  return 1;
}
