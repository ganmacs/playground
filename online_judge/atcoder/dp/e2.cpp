#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

const long long INF = 1e18;

long long dp[112345], w[112345], v[112345];

int main()
{
  int N, W;
  long long va = 0;
  cin >> N >> W;

  for (int i = 0; i < N; i++) {
    cin >> w[i] >> v[i];
    va += v[i];
  }

  fill(dp, dp + va + 1, INF);
  dp[0] = 0;
  for (int i = 0; i < N; i++) {
    for (long long j = va; (j - v[i]) >= 0; j--) {
      dp[j] = min(dp[j], dp[j-v[i]] + w[i]);
    }
  }

  for (long long i = va; (i-v[i] >= 0); i--) {
    if (dp[i] <= W) {
      cout << i << endl;
      return 0;
    }
  }

  return 0;
}
