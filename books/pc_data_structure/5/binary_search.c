#include <stdio.h>
#include <stdlib.h>

int mbsearch(int t, int ary[], int r)
{
  int l = 0, m;

  while (l < r) {
    m = (l + r) / 2;
    if (ary[m] == t) {
      return 1;                 /* found */
    } else if (ary[m] < t) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int n, qn, i, sum = 0, t;
  int N[100000];

  scanf("%d", &n);
  for (i = 0; i < n; i++) { scanf("%d", &N[i]); }

  scanf("%d", &qn);
  for (i = 0; i < qn; i++) {
    scanf("%d", &t);
    if (mbsearch(t, N, n)) sum++;
  }

  printf("%d\n", sum);
  return 0;
}
