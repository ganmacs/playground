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

long long dp[102][112345];

int main()
{
  int N, v;
  long long W, w;
  cin >> N >> W;

  vector<pair<long long, int> > b(N);
  for (auto& vi: b) {
    cin >> w >> v;
    vi = make_pair(w, v);
  };

  fill(dp[0], dp[0] + 100002, INF);
  dp[0][0] = 0;

  for (int i = 0; i < N; i++) {
    auto w = b[i].first;
    auto v = b[i].second;

    for (int j = 0; j <= 100001; j++) {
      if (j >= v && (w + dp[i][j-v]) <= W) {
        dp[i + 1][j] = min(w + dp[i][j-v], dp[i][j]);
      } else {
        dp[i + 1][j] = dp[i][j];
      }
    }
  }

  for (int i = 100001; i >= 0; i--) {
    if (dp[N][i] == INF) continue;
    cout << i << endl;
    break;
  }

  return 0;
}
