#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int
comp_func (const void *c1, const void *c2)
{
  int i1 = *(int *)c1;
  int i2 = *(int *)c2;
  return i1 - i2;
}

void
fyshuffle(int* v, int n)
{
  srand((unsigned)time(NULL));

  for (int i = 0; i < n; i++) {
    v[i] = i;
  }

  for (int i = n - 1; i >= 0 ; i--) {
    int rnd = rand() % n;
    int tmp = v[i];
    v[i] = v[rnd];
    v[rnd] = tmp;
  }
}

int
main(int argc, char *argv[])
{
  int seed[N];
  fyshuffle(seed, N);

  qsort(seed, N, sizeof(int), comp_func);

  for (int i = 0; i < N; i++) {
    printf("%d\n", seed[i]);
  }

  return 0;
}
