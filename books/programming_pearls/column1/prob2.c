#include <stdio.h>
#include <stdlib.h>

#define N 100
#define INT_LEN(n) (int)(sizeof(n) / sizeof(int))

void
print_bin(int v[], int size)
{
  for (int i = 0; i < size; i++) {
    if (v[i] == 0) {
      printf("%d", 0);
    } else {
      printf("%d", 1);
    }
  }
  puts("");
}

void
set(int v[], int i)
{
  v[1 << i] = 1;
}

void
clear(int v[], int i)
{
  v[1 << i] = 0;
}


int
main(int argc, char *argv[])
{
  int seed[] = {10, 77, 82, 30, 2, 40, 100, 1, 60, 4, 40, 99, 13, 83, 31, 69, 63, 8, 71, 97, 55, 86, 29};

  int result[N];

  for (int i = 0; i < N; i++) {
    result[i] = 0;
  }


  /* set */

  for (int i = 0; i < INT_LEN(seed); i++) {
    set(result, seed[i]);
  }

  for (int i = 0; i < N; i++) {
    if (result[i] == 1) printf("%d, ", i);
  }

  puts("");

  /* clear */

  for (int i = 0; i < INT_LEN(seed); i++) {
    clear(result, seed[i]);
  }

  for (int i = 0; i < N; i++) {
    if (result[i] == 1) printf("%d, ", i);
  }

  puts("");
}
