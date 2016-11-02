#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n, qn, i, j, sum = 0;
  int N[10000 + 1], q;

  scanf("%d", &n);
  for (i = 0; i < n; i++) { scanf("%d", &N[i]); }

  scanf("%d", &qn);
  for (i = 0; i < qn; i++) {
    scanf("%d", &N[n]);
    j = 0;
    while (N[j] != N[n]) j++;
    if (j != n) sum++;
  }

  printf("%d\n", sum);

  return 0;
}
