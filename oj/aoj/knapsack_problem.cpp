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
typedef pair<int,int> P;
static const int MAX = 10000;
static const int MAX_I = 100;

long long dp[MAX_I + 1][MAX + 1];
int v[MAX_I + 1], w[MAX_I + 1];

int main() {
  int N, W;
  cin >> N >> W;

  for (int i = 1; i <= N; i++) {
    cin >> v[i] >> w[i];
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= W; j++) {
      if (j >= w[i]) {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i]] + v[i]);
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }
  cout << dp[N][W] << endl;
}
