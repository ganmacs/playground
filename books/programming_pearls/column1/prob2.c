#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define WORD 8
#define SHIFT 3

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

int
main(int argc, char *argv[])
{
  int seed[N];
  fyshuffle(seed, N);

  int size = N / WORD + 1;
  int result[size];

  for (int i = 0; i < size; i++) {
    result[i] = 0;
  }

  /* set */

  for (int i = 0; i < N; i++) {
    set(result, seed[i]);
  }

  for (int i = 0; i < size; i++) {
    print_bin2(result[i]);
  }

  ppp(result, size);


  /* clear */

  for (int i = 0; i < N; i++) {
    clear(result, seed[i]);
  }

  for (int i = 0; i < size; i++) {
    print_bin2(result[i]);
  }

  ppp(result, size);
}
