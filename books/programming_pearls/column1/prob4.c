/* Fisher–Yates shuffle algorithm */
#include "fisher_yates.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int
main(int argc, char *argv[])
{
  int *v = fyshuffle(N);

  for (int i = 0; i < N; i++) {
    printf("%d\n", v[i]);
  }

  free(v);
  return 0;
}
