#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fisher_yates.c"

#define N 1000000
#define WORD 128
#define SHIFT 7

void shuffle_performance(char* desc, void (*target)(int*)) {
  int *v = fyshuffle(N);
  clock_t start, end;
  start = clock();

  target(v);

  end = clock();
  printf("=======================\nName: %s\nTime:%lu[ms]\n=======================\n", desc, end - start);
  free(v);
}


int
comp_func (const void *c1, const void *c2)
{
  int i1 = *(int *)c1;
  int i2 = *(int *)c2;
  return i1 - i2;
}

void
test1(int *v)
{
  qsort(v, N, sizeof(int), comp_func);
}


void
test2(int *v)
{
  int s[N];

  for (int i = 0; i < N; i++) {
    s[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    s[v[i]] = 1;
  }
}

void
set(int v[], int i)
{
  v[i >> SHIFT] |= 1 << ((WORD - 1) & i);
}

void
test3(int *v)
{
  int s[N];

  for (int i = 0; i < N; i++) {
    s[i] = 0;
  }


  for (int i = 0; i < N; i++) {
    set(s, v[i]);
  }
}

int main(int argc, char *argv[])
{


  shuffle_performance("qsort", test1);
  shuffle_performance("bit", test2);
  shuffle_performance("bitsort", test3);

  return 0;
}
