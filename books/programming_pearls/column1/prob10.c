/* 番号のしもn桁により分類する */

#include <stdio.h>
#include <stdlib.h>

typedef struct pn {
  int number;
  struct pn* next;
} pn_t;

int
main(int argc, char *argv[])
{
  pn_t* ary[10][10];
  int seed[] = { 100010, 100021, 100089, 200021, 200078, 200067, 200000 };
  int size = sizeof(seed) / sizeof(int);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ary[i][j] = NULL;
    }
  }

  for (int i = 0; i < size; i++) {
    int k_i = (seed[i] % 100) / 10;
    int k_j = seed[i] % 10;

    pn_t* v = malloc(sizeof(pn_t));
    if (v == NULL) {
      printf("malloc failed\n");
      return 1;
    }
    v->number = seed[i];
    v->next = NULL;

    if (ary[k_i][k_j] == NULL) {
      ary[k_i][k_j] = v;
    } else {
      pn_t* t = ary[k_i][k_j];

      while (t->next != NULL) {
        t = t->next;
      }
      t->next = v;
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      pn_t* t = ary[i][j];
      while (t != NULL) {
        printf("ary[%d][%d]=%d\n", i, j, t->number);
        t = t->next;
      }
    }
  }

  return 0;
}
