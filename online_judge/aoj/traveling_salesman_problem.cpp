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

int tsp(int s, int v)
{
  if (dp[s][v] >= 0) {
    return dp[s][v];
  }

  // finish?
  if (s == (1 << n)-1 && v == 0) {
    return dp[s][v] = 0;
  }

  int res = INF;
  for (int i = 0; i < n; i++) {
    if ((s >> i) & 1) continue; // visited?
    res = min(res, tsp(s | (1 << i), i) + M[v][i]);
  }

  return res;
}

int main(){
  cin >> n >> e;

  for (int i = 0; i < 15; i++)
    for (int j = 0; j < 15; j++)
      M[i][j] = INF;

  for (int i = 0; i < MAX; i++)
    fill_n(dp[i], 15, -1);

  int a, b, c;
  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    M[a][b] = c;
  }

  int v = tsp(0, 0);
  cout <<  (v == INF ? -1 : v) << endl;
}
