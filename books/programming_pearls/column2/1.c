/* 与えられた文字列と辞書の */
/* 文字列自体をソートして同じ文字列のものを探す */

/* 同じサイズに並び替えておく */

/* A.辞書の単語全てに対してシグネチャを作成してその後2分探索する */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util.c"

#define N 5

int comp_func (const void *c1, const void *c2)
{
  char i1 = *(char *)c1;
  char i2 = *(char *)c2;

  return i1 - i2;
}

int comp_func2 (const void *c1, const void *c2)
{
  char* i1 = *(char **)c1;
  char* i2 = *(char **)c2;
  return strcmp(i1, i2);
}

void no_mem()
{
  char* a[N] = {"deposit", "topic", "posited", "asdf", "delight"};
  char* target = "deopsit";
  char signature[10];
  char s[10];

  strcpy(signature, target);
  qsort(signature, strlen(signature), sizeof(char), comp_func);

  for (int i = 0; i < N; i++) {
    strcpy(s, a[i]);
    qsort(s, strlen(s), sizeof(char), comp_func);
    if(strcmp(s, signature) == 0) {
      printf("%s\n", a[i]);
    }
  }
}

int kvs_sort (const void *c1, const void *c2)
{
  KV *i1 = *(KV **)c1;
  KV *i2 = *(KV **)c2;

  return strcmp((char*)i1->val, (char*)i2->val);
}


void on_mem()
{
  char* a[N] = {"deposit", "topic", "posited", "asdf", "delight"};
  char* target = "deopsit";
  char signature[10];
  KVs* kvs = new_kvs();

  strcpy(signature, target);
  qsort(signature, strlen(signature), sizeof(char), comp_func);

  for (int i = 0; i < N; i++) {
    char* s = malloc(sizeof(a[i]));
    strcpy(s, a[i]);
    qsort(s, strlen(s), sizeof(char), comp_func);

    kvs_insert(kvs, a[i], s);
  }

  for (int i = 0; i < kvs->celem; i++) {
    printf("%s: %s\n", (char *)(kvs_get(kvs, i)->key), (char *)(kvs_get(kvs, i)->val));
  }

  qsort(kvs->body, kvs->celem, sizeof(KV *), kvs_sort);
  puts("-------");

  for (int i = 0; i < kvs->celem; i++) {
    printf("%s: %s\n", (char *)(kvs_get(kvs, i)->key), (char *)(kvs_get(kvs, i)->val));
  }

  puts("-------");


  int l = 0;
  int r = kvs->celem;

  while (l < r) {
    int p = (l +  r) / 2;

    KV *k = kvs_get(kvs, p);

    if (strcmp(k->val, signature) > 0) {
      r = p;
    } else if (strcmp(k->val, signature) < 0) {
      l = p;
    } else {
      /* found */
      for (int i = p + 1; i < kvs->celem; i++) {
        KV *k2 = kvs_get(kvs, i);
        if (strcmp(k2->val, signature)) break;
        printf("%s\n", (char *)(kvs_get(kvs, i)->key));
      }
      for (int i = p ; i >= 0; i--) {
        KV *k2 = kvs_get(kvs, i);
        if (strcmp(k2->val, signature)) break;
        printf("%s\n", (char *)(kvs_get(kvs, i)->key));
      }
      return;
    }
  }
}



int main(int argc, char *argv[])
{
  no_mem();
  on_mem();
  return 0;
}
