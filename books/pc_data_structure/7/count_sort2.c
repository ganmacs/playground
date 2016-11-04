#include <stdio.h>

#define M 10001

int main(int argc, char *argv[])
{
  int n, i, v, K[M];

  scanf("%d", &n);
  for (i = 0; i < M ; i++) K[i] = 0;
  for (i = 0; i < n; i++) { scanf("%d", &v); K[v]++; }

  int j = 0;
  for (i = 0; i < M; i++) {
    while (K[i] > 0) {
      if (j != 0) printf(" ");
      j++;
      printf("%d", i);
      K[i]--;
    }
  }

  puts("");

  return 0;
}
