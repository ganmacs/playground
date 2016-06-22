#include "fisher_yates.c"
#include "bit.c"

#define N 100
#define WORD 8
#define SHIFT 3

/* 0 - 5Mbit */

/* 5,000,001 - 10Mbit */
/* の2回をやる。 */
/* 計算時間は回数kに比例するのでソートする整数の大きさをnとすると */

/* T = kn */

/* となる。 */

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

int main(int argc, char *argv[])
{

  int *v = fyshuffle(N);

  printf("%d\n", 10);

  int s[N];

  for (int i = 0; i < N; i++) {
    s[i] = 0;
  }

  /* for (int i = 0; i < N; i++) { */
  /*   if (v[i] >= 0 &&  v[i] < (N/2)) { */
  /*     set(s, v[i]); */
  /*   } */
  /* } */

  /* for (int i = 0; i < N; i++) { */
  /*   if (v[i] >= (N/2) + 1 &&  v[i] < N) { */
  /*     set(s, v[i]); */
  /*   } */
  /* } */

  ppp(v, N);

  free(v);
  return 0;
}
