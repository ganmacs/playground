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
static const int INF = 1 << 16;
static const int MAX = 1 << 15;

int n, e, dp[MAX][15];
int M[15][15];

int tsp()
{
  for (int i = 0; i < MAX; i++)
    fill_n(dp[i], 15, INF);
  dp[(1 << n) -1][0] = 0;

  for (int i = (1 << n) - 2; i >= 0; i--) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if ((i >> k) & 1) continue; // already visited
        dp[i][j] = min(dp[i][j], M[j][k] + dp[i | 1 << k][k]);
      }
    }
  }

  return dp[0][0];
}

int main()
{
  cin >> n >> e;

  for (int i = 0; i < 15; i++)
    for (int j = 0; j < 15; j++)
      M[i][j] = INF;

  int a, b, c;
  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    M[a][b] = c;
  }

  int v = tsp();
  cout <<  (v == INF ? -1 : v) << endl;
}
