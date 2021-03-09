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

const long long int INF = 1e9;
const long long int INF2 = 100000;
long long dp[112345], w[105], v[105];

int main(int argc, char *argv[])
{
  long long N, W, v, w, va = 0;
  cin >> N >> W;

  std::fill(dp, dp + 100002, INF);
  dp[0] = 0;

  for (int i = 0; i < N; i++) {
    cin >> w >> v;
    va += v;

    for (int j = INF2; j >= v; j--) {
      dp[j] = min(dp[j], dp[j-v] + w);
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
