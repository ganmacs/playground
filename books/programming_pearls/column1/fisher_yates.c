/* Fisher–Yates shuffle algorithm */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int*
fyshuffle(int n)
{
  int *v;
  if ((v = (int*)malloc(sizeof(int) * n)) == NULL) return NULL;

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

  return v;
}
