#include <stdio.h>

int n, A[100];

int solve(int i, int sum, int m)
{
  if (sum == m) return 1;
  if (i == n) return 0;
  return solve(i + 1, sum, m) + solve(i + 1, sum + A[i], m);
}

int main(int argc, char *argv[])
{
  int m, q, i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) { scanf("%d", &A[i]); }

  scanf("%d", &q);
  for (i = 0; i < q; i++) {
    scanf("%d", &m);
    if (solve(0, 0, m)) {
      puts("yes");
    } else {
      puts("no");
    }
  }
  return 0;
}
