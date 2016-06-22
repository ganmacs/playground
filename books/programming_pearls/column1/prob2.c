#include <stdio.h>
#include <stdlib.h>

#define N 100
#define WORD 8
#define SHIFT 3

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
print_bin2(int v)
{
  if (v == 0) {
    for (int i = 0; i < 8; i++) {
      printf("%d", 0);
    }
    puts("");
    return;
  }

  for (int i = WORD - 1; i >= 0; i--) {
    if (((v >> i) & 1) == 0) {
      printf("%d", 0);
    } else {
      printf("%d", 1);
    }
  }

  puts("");
}

void
ppp(int v[], int size)
{
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < WORD; j++) {
      if (v[i] == 0) continue;
      if (((v[i] >> j) & 1) == 1) {
        printf("%d, ", (WORD * i) + j);
      }
    }
  }
  puts("");
}


void
set(int v[], int i)
{
  v[i >> SHIFT] |= 1 << ((WORD - 1) & i);
}

void
clear(int v[], int i)
{
  v[i >> SHIFT] &= ~(1 << ((WORD - 1) & i));
}


int
main(int argc, char *argv[])
{
  int seed[] = {0, 10, 77, 82, 30, 2, 40, 98, 1, 60, 4, 40, 99, 13, 83, 31, 69, 63, 8, 71, 97, 55, 86, 29};

  int size = N / WORD + 1;
  int result[size];

  for (int i = 0; i < size; i++) {
    result[i] = 0;
  }

  /* set */

  for (int i = 0; i < INT_LEN(seed); i++) {
    set(result, seed[i]);
  }

  for (int i = 0; i < size; i++) {
    print_bin2(result[i]);
  }

  ppp(result, size);


  /* clear */

  for (int i = 0; i < INT_LEN(seed); i++) {
    clear(result, seed[i]);
  }

  for (int i = 0; i < size; i++) {
    print_bin2(result[i]);
  }

  ppp(result, size);
}
