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


long long dp[112345];

int main()
{
  int N, W;
  long long w, v, va = 0;
  vector<pair<long long,  long long>> V;
  cin >> N >> W;

  for (int i = 0; i < N; i++) {
    cin >> w >> v;
    V.push_back(make_pair(w, v));
    va += v;
  }
  fill(dp, dp + va + 10, INF);

  dp[0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = va; (j - V[i].second) >= 0; j--) {
      dp[j] = min(dp[j], dp[j-V[i].second] + V[i].first);
    }
  }

  for (int i = va; i >= 0; i--) {
    if (dp[i] <= W) {
      cout << i << endl;
      return 0;
    }
  }

  return 0;
}
