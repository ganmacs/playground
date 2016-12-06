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
static const int MAX = 2000;
static const int GMAX = 10;
int n;

int main(){
  vector<int> g[GMAX + 1];
  int p[GMAX + 1][MAX + 1];
  int dp[GMAX + 1][MAX + 1];
  int n, k, a, b;

  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    g[b-1].push_back(a);
  }

  for (int i = 0; i < GMAX; i++) {
    fill_n(dp[i], n, 0);
    fill_n(p[i], n, 0);
  }

  for (int i = 0; i < GMAX; i++) {
    sort(g[i].begin(), g[i].end(), greater<int>());
    for (int j = 0; j < (int)g[i].size(); j++) {
      p[i][j + 1] = p[i][j] + g[i][j] + 2 * j; // (j+1)j - (j(j-1))
    }
  }

  for (int i = 0; i < GMAX; i++) {
    for (int j = 0; j < k; j++) {
      for (int l = 1; l < (int)g[i].size()+1; l++) {
        if (j + 1 - l >= 0) {
          dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j+1-l] + p[i][l]);
        }
      }
    }
    for (int j = 0; j < (k + 1); j++) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
  }
  cout << dp[GMAX][k] << endl;
}
