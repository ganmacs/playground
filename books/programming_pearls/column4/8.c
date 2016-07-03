#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int b_search(int t, int ary[], int size)
{
  int l = 0, r = size - 1, p;

  while (l <= r) {
    p = (l + r) / 2;
    if (t > ary[p])      l = p + 1;
    else if (t < ary[p]) r = p - 1;
    else {
      return p;
    }
  }
  return - 1;
}

int b_search2(int t, int ary[], int size)
{
  int l = 0;
  int i = 512;

  if (ary[i - 1] < t) l = N - i; /* the number of list lenght is 512 */

  while (i != 1) {
    i >>= 1;

    if (ary[i + l] < t) {
      l += i;
    }
  }

  int p = l + 1;
  if (p < N &&  ary[p] == t)
    return p;

  return - 1;
}


int main(int argc, char *argv[])
{
  int in[N];
  for (int i = 0; i < N; i++) in[i] = i;

  clock_t start, end;
  float sum1 = 0, sum2 = 0;

  for (int i = 0; i < N; i++) {
    start = clock();
    b_search2(1, in, N);
    end = clock();
    sum2 += (start - end);
  }
  printf("%f\n", sum2 / N);

  for (int i = 0; i < N; i++) {
    start = clock();
    b_search(1, in, N);
    end = clock();
    sum1 += (start - end);
  }
  printf("%f\n", sum1 / N);


  return 0;
}
