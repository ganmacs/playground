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
  int N = S.size();

  fill(dp[1], dp[1] + N, 0);
  fill(dp[2], dp[2] + N, 0);

  dp[1][0] = 1;

  for (int i = 1; i < N; i++) {
    if (S[i] != S[i-1]) {       // 1 -> 1
      dp[1][i] = max(dp[1][i-1] + 1, dp[1][i]);
    }

    dp[1][i] = max(dp[2][i-1] + 1, dp[1][i]); // 2 -> 1


    if (i - 2 >= 0) {            // 1 -> 2
      dp[2][i] = max(dp[1][i-2] + 1, dp[2][i]);
    }

    if (i - 3 >= 0 && (S[i] != S[i-2] || S[i-1] != S[i-3])) {            // 2 -> 2
      dp[2][i] = max(dp[2][i-2] + 1, dp[2][i]);
    }
  }

  cout << max(dp[1][N-1], dp[2][N-1]) << endl;

  return 0;
}
