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

unsigned long long dp[101][112345];

int main(int argc, char *argv[])
{
  unsigned long long N, W, w, v;

  cin >> N >> W;
  for (int i = 0; i < W; i++) {
    dp[0][i] = 0;
  }


  for (int i = 1; i < N + 1; i++) {
    cin >> w >> v;

    for (int j = 0; j <= W; j++) {
      if (j >= w) {
        dp[i][j] = max(dp[i-1][j], v + dp[i-1][j-w]);
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }

  }


  cout << dp[N][W] << endl;
  return 0;
}
