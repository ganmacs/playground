/* ru314/8cc */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Map */

#define INIT_SIZE 16

typedef struct Map {
  char **key;
  void **val;
  int size;
  int celem;
} Map;

// FNV hash
uint32_t hash(char *p)
{
  uint32_t r = 2166136261;
  for (; *p; p++) {
    r ^= *p;
    r *= 16777619;
  }

  return r;
}

void maybe_rehash(Map *m)
{
  if (m->celem < (m->size * 0.7)) return;
  int newsize = m->size * 2;
  int mask = newsize - 1;
  char **key = calloc(newsize, sizeof(char *));
  void **val = calloc(newsize, sizeof(void *));

  for (int i = 0; i < m->size; i++) {
    if (m->key[i] == NULL) continue;

    int j = hash(m->key[i]) & mask;
    for (;; j = (j + 1) & mask) {
      if (key[j] != NULL) continue;
      key[j] = m->key[i];
      val[j] = m->val[i];
      break;
    }
  }

  free(m->key);
  free(m->val);

  m->key = key;
  m->val = val;
  m->size = newsize;
}

Map *do_make_map(int size)
{
  Map *new = malloc(sizeof(Map));
  new->key = calloc(size, sizeof(char *));
  new->val = calloc(size, sizeof(void *));
  new->size = size;
  new->celem = 0;

  return new;
}

Map *new_map()
{
  return do_make_map(INIT_SIZE);
}

void map_put(Map *m, char* key, void* val)
{
  maybe_rehash(m);
  int mask = m->size - 1;
  int h = hash(key) & mask;

  for (;; h = (h + 1) & mask) {
    char *k = m->key[h];
    if (k == NULL) {
      m->key[h] = key;
      m->val[h] = val;
      m->celem++;
      return;
    }

    if (!strcmp(key, k)) {
      m->val[h] = val;
      return;
    }
  }
}

void *map_get(Map *m, char* key)
{
  int mask = m->size - 1;
  int h = hash(key) & mask;

  for (; m->key[h] != NULL; h = (h + 1) & mask) {
    if (!strcmp(m->key[h], key)) {
      return m->val[h];
    }
  }
  return NULL;
}

int map_size(Map *m)
{
  return m->size;
}


/* PairList */

typedef struct KV {
  char *key;
  void *val;
} KV;

typedef struct KVs {
  int size;
  int celem;
  KV **body;
} KVs;

KVs* do_make_kvs(int size)
{
  KVs *kvs = malloc(sizeof(KVs));
  kvs->size = size;
  kvs->celem = 0;
  kvs->body = calloc(size, sizeof(KV *));
  return kvs;
}

KVs* new_kvs()
{
  return do_make_kvs(INIT_SIZE);
}

void kvs_insert(KVs *kvs, char* key, void *val)
{
  if (kvs->celem > (kvs->size * 0.7)) {
    int new_size = kvs->size * 2;
    KV **body = calloc(new_size, sizeof(KV *));

    for (int i = 0; i < kvs->celem; i++) {
      body[i] = kvs->body[i];
    }

    free(kvs->body);
    kvs->size = new_size;
  }

  KV *kv = malloc(sizeof(KV));
  kv->key = key;
  kv->val = val;
  kvs->body[kvs->celem] = kv;
  kvs->celem++;
}

KV *kvs_get(KVs *kvs, int i)
{
  if (kvs->celem < i) return NULL;
  return kvs->body[i];
}

/* int main(int argc, char *argv[]) */
/* { */
/*   KVs *k = new_KVs(); */
/*   kvs_insert(k, "k0",  "v0"); */
/*   kvs_insert(k, "k1",  "v1"); */
/*   kvs_insert(k, "k2",  "v2"); */
/*   kvs_insert(k, "k3",  "v3"); */
/*   kvs_insert(k, "k4",  "v4"); */
/*   kvs_insert(k, "k5",  "v5"); */
/*   kvs_insert(k, "k6",  "v6"); */
/*   kvs_insert(k, "k7",  "v7"); */
/*   kvs_insert(k, "k8",  "v8"); */
/*   kvs_insert(k, "k9",  "v9"); */
/*   kvs_insert(k, "k10",  "v10"); */
/*   kvs_insert(k, "k11",  "v11"); */
/*   kvs_insert(k, "k12",  "v12"); */

/*   printf("%d\n", k->size); */

/*   for (int i = 0; i < k->celem; i++) { */
/*     printf("%s\n", (char *)(kvs_get(k, i)->key)); */
/*   } */

/*   return 0; */
/* } */




/* int main(int argc, char *argv[]) */
/* { */
/*   Map *m = new_map(); */

/*   map_put(m, "key", "value"); */
/*   map_put(m, "key1", "value2"); */
/*   map_put(m, "key2", "value2"); */
/*   map_put(m, "key3", "value3"); */
/*   map_put(m, "key4", "value4"); */
/*   map_put(m, "key5", "value5"); */
/*   map_put(m, "key6", "value6"); */
/*   map_put(m, "key7", "value7"); */
/*   map_put(m, "key8", "value8"); */
/*   map_put(m, "key9", "value9"); */
/*   map_put(m, "key10", "value10"); */
/*   map_put(m, "key11", "value11"); */
/*   map_put(m, "key12", "value12"); */
/*   map_put(m, "key13", "value13"); */
/*   map_put(m, "key14", "value14"); */

/*   printf("%d\n", map_size(m)); */

/*   printf("%s\n", (char*) map_get(m, "key")); */
/*   printf("%s\n", (char*) map_get(m, "key1")); */
/*   printf("%s\n", (char*) map_get(m, "key2")); */
/*   printf("%s\n", (char*) map_get(m, "key3")); */
/*   printf("%s\n", (char*) map_get(m, "key4")); */
/*   printf("%s\n", (char*) map_get(m, "key5")); */
/*   printf("%s\n", (char*) map_get(m, "key6")); */
/*   printf("%s\n", (char*) map_get(m, "key7")); */
/*   printf("%s\n", (char*) map_get(m, "key8")); */
/*   printf("%s\n", (char*) map_get(m, "key9")); */
/*   printf("%s\n", (char*) map_get(m, "key10")); */
/*   printf("%s\n", (char*) map_get(m, "key11")); */
/*   printf("%s\n", (char*) map_get(m, "key12")); */
/*   printf("%s\n", (char*) map_get(m, "key13")); */
/*   printf("%s\n", (char*) map_get(m, "key14")); */



/*   return 0; */
/* } */
