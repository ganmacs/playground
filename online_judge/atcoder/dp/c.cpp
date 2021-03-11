#include <algorithm>
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

long long dp[3][112345];

int main(int argc, char *argv[])
{
  long long N, a, b, c;
  cin >> N;
  dp[0][0] = 0;
  dp[1][0] = 0;
  dp[2][0] = 0;

  for (int i = 1; i < N + 1; i++) {
    cin >> a >> b >> c;
    dp[0][i] = a + max(dp[1][i-1], dp[2][i-1]);
    dp[1][i] = b + max(dp[0][i-1], dp[2][i-1]);
    dp[2][i] = c + max(dp[1][i-1], dp[0][i-1]);
  }

  long long ans = 0;
  for (int i = 0; i < 3; i++) {
    ans = max(ans, dp[i][N]);
  }

  cout << ans << endl;
  return 0;
}
