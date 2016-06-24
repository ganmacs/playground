#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define WORD 32
#define SHIFT 5

void
set(int v[], int i)
{
  if (i < 0 || i > N) {
    printf("Invalid Number %d\n", i);
    exit(1);
  } else if (v[i >> SHIFT] == 1) {
    printf("Duplicate Number %d\n", i);
    exit(1);
  }

  v[i >> SHIFT] |= 1 << (WORD - 1 & i);
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

  int size = N / WORD + 1;
  int v[size];
  for (int i = 0; i < size; i++) v[i] = 0;

  /* create bitmap */
  for (int i = 0; i < N; i++) set(v, seed[i]);

  for (int i = 0; i < size; i++) {
    for (int j = WORD - 1; j >= 0; j--) {
      if ((v[i] >> j) & 1) {
        printf("%2d, ", (WORD * i) + j);
      }
    }
    puts("");
  }

  return 0;
}
