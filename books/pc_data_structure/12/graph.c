#include <stdio.h>
#include <stdlib.h>

const int M = 102;

int main(int argc, char *argv[])
{
  int n, ni, k, v, i, j;
  int t[M][M];

  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) t[i][j] = 0;
  }

  for (i = 0; i < n; i++) {
    scanf("%d %d", &ni, &k);
    for (j = 0; j < k; j++) {
      scanf("%d", &v);
      t[ni][v] = 1;
    }
  }

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (j != 1) printf(" ");
      printf("%d", t[i][j]);
    }
    puts("");
  }

  return 0;
}
