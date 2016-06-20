#include <stdio.h>
#include <stdlib.h>

#define N 100
#define INT_LEN(n) (int)(sizeof(n) / sizeof(int))

int
comp_func (const void *c1, const void *c2)
{
  int i1 = *(int *)c1;
  int i2 = *(int *)c2;
  return i1 - i2;
}


int
main(int argc, char *argv[])
{
  int seed[] = {10, 77, 82, 30, 2, 40, 100, 1, 60, 4, 40, 99, 13, 83, 31, 69, 63, 8, 71, 97, 55, 86, 29};

  qsort(seed, INT_LEN(seed), sizeof(int), comp_func);

  for (int i = 0; i < INT_LEN(seed); i++) {
    printf("%d\n", seed[i]);
  }

  return 0;
}
