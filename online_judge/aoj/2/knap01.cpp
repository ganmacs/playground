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
static const int MAX = 10000;

int dp[101][MAX + 1];

int main()
{
  int N, W;
  cin >> N >> W;

  for (int i = 0; i < N; i++)
    fill_n(dp[i], W + 1, 0);

  int v, w;
  for (int i = 0; i < N; i++) {
    cin >> v >> w;
    for (int j = 1; j <= W; j++) {
      if (j - w >= 0) {
        dp[i + 1][j] = max(dp[i][j], dp[i][j-w] + v);
      } else {
        dp[i + 1][j] = dp[i][j];
      }
    }
  }

  cout << dp[N][W] << endl;
}
