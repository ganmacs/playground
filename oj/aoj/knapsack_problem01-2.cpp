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
static const int INF = 1e9 + 1;
static const int MAX = 10001;
int dp[MAX];
int N, W, v, w;

int main()
{
  cin >> N >> W;

  fill_n(dp, MAX, INF);
  dp[0] = 0;

  for (int i = 0; i < N; i++) {
    cin >> v >> w;
    for (int j = MAX-1; j >= v; j--) {
      if ((dp[j-v] + w < dp[j]) ) {
        dp[j] = min(dp[j], dp[j-v] + w);
      }
    }
  }

  for (int k = MAX-1; k >= 0; k--) {
    if (dp[k] <= W) {
      cout << k << endl;
      break;
    }
  }

  return 0;
}
