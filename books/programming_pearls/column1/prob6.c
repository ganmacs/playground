/* 10を4bitで表す。 */
/* すると 1M byte * 4 必要 */
/* ポインタにするのではなく4ビットずつを1つの列に押し込める */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

#define T_SHIFT 2
#define T 4

#define SHIFT 3
#define WORD 8

/* skip 10 check */

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
binc(int v, int base)
{
  return (v + (1 << base));
}

void
set(int v[], int i)
{
  v[i >> SHIFT] += binc(v[i >> SHIFT], ((WORD - 1) & i) * T);
}

int
main(int argc, char *argv[])
{
  int seed[N];
  fyshuffle(seed, N);

  int size = N / WORD + 1;
  int v[size];
  for (int i = 0; i < size; i++) v[i] = 0;
  for (int i = 0; i < N; i++) set(v, seed[i]);

  for (int i = 0; i < size; i++) {
    for (int j = WORD - 1; j >= 0; j--) {
      int k = (v[i] >> (j << T_SHIFT)) % 10;
      printf("%d, ", k);
      /* if () {   /\* 1111 *\/ */
      /*   printf("%2d, ", (WORD * i) + j); */
      /* } */
    }
    puts("");
  }

}
