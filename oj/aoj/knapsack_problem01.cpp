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
static const double EPS = 1e-8;
static const int MAX = 10000;
static const int MAX_I = 100;

int dp[MAX_I + 1][MAX + 1];
P items[MAX_I + 1];

int main()
{
  int n, w, a, b;
  cin >> n >> w;
  for (int i = 1; i <= n; i++) {
    cin >> a >> b;
    items[i] = P(a, b);
  }

  for (int i = 0; i <= n; i++)
    fill_n(dp[i], w + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= w; j++) {
      int weight = items[i].second;
      int cost = items[i].first;
      if (j - weight >= 0) {
        dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight] + cost);
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }
  cout << dp[n][w] << endl;
}
