#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int dp[3][212345];

int
main()
{
  string S;
  cin >> S;
  int N = S.length();

  fill(dp[1], dp[1] + N, 0);
  fill(dp[2], dp[2] + N, 0);
  dp[1][0] = 1;

  for (int i = 1; i < N; i++) {
    if (S[i-1] != S[i]) {       // 1 -> 1
      dp[1][i] = max(dp[1][i], dp[1][i-1] + 1);
    }

    // 2 -> 1
    dp[1][i] = max(dp[1][i], dp[2][i-1] + 1);

    if (i - 2 >= 0) {            // 1 -> 2
      dp[2][i] = max(dp[2][i], dp[1][i-2] + 1);
    }

    if (i - 3 >= 0) {            // 2 -> 2
      if (S[i-2] != S[i] || S[i-3] != S[i-1]) {
        dp[2][i] = max(dp[2][i], dp[2][i-3] + 1);
      }
    }
  }

  cout << max(dp[1][N-1], dp[2][N-1]) << endl;
  return 0;
}
