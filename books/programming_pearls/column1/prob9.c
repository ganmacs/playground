#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20

void
fyshuffle(int* v, int n)
{
  srand((unsigned)time(NULL));

  for (int i = 0; i < n ; i++) {
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
  srand((unsigned)time(NULL));
  int ary[N], from[N], to[N];

  /* to check to work */
  for (int i = 0; i < N; i++) {
    ary[i] = 0;
    from[i] = -1;
    to[i] = 0;
  }

  int top = 0;

  int seed[N];
  fyshuffle(seed, N);

  for (int i = 1; i < 11; i++) {
    int j = seed[i];

    printf("%d\n", j);
    if ((from[j] > top) || (from[j] < 0) || to[from[j]] != i) {
      from[j] = top;
      to[top] = i;
      top++;
    }

    ary[j] = i;               /* i is meanless */
  }

  printf("ary:  ");
  for (int i = 0; i < N; i++) {
    if (ary[i] > N || ary[i] <=  0) {
      printf("-- ");
    } else {
      printf("%2d ", ary[i]);
    }
  }
  puts("");

  printf("from: ");
  for (int i = 0; i < N; i++) {
    if (from[i] > N || from[i] < 0) {
      printf("-- ");
    } else {
      printf("%2d ", from[i]);
    }
  }
  puts("");

  printf("to:   ");
  for (int i = 0; i < N; i++) {
    if (to[i] > N || to[i] <= 0) {
      printf("-- ");
    } else {
      printf("%2d ", to[i]);
    }
  }
  puts("");

  return 0;
}
