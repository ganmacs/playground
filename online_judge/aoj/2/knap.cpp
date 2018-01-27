#include <iostream>
#include <sstream>

using namespace std;
static const int MAX = 100000;

int dp[MAX + 1];

int main() {
  int N, W;
  int v, w;
  cin >> N >> W;

  dp[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> v >> w;
    for (int j = 1; j <= W; j++) {
      if (j - w >= 0) {
        dp[j] = max(dp[j-w] + v, dp[j]);
      }
    }
  }

  cout << dp[W] << endl;
}
