#include <stdio.h>

int n, A[100];
int dp[100][100];
int m;

int solve(int i, int sum, int m)
{
  if (sum == m) return 1;
  if (i == n) return 0;
  return solve(i + 1, sum, m) + solve(i + 1, sum + A[i], m);
}

int solve2(int i, int sum)
{
  if (dp[i][sum] != -1) return dp[i][sum];

  if (sum == m) {
    dp[i][sum] = 1;
  } else if(i >= m) {
    dp[i][sum] = 0;
  } else if (solve2(i + 1, sum)) {
    dp[i][sum] = 1;
  } else if (solve2(i + 1, sum + A[i])) {
    dp[i][sum] = 1;
  } else {
    dp[i][sum] = 0;
  }

  return dp[i][sum];
}

int main(int argc, char *argv[])
{
  int k, q, i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) { scanf("%d", &A[i]); }

  scanf("%d", &q);
  for (i = 0; i < q; i++) {
    scanf("%d", &k);
    if (solve(0, 0, k)) {
      puts("yes");
    } else {
      puts("no");
    }
  }
  return 0;
}
