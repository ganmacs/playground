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
typedef long long ll;
static const int MAX = 50000;

ll dp[20 + 2][MAX + 2];

int main(){
  int n, m;
  ll coins[20];
  cin >> n >> m;

  fill_n(dp[0], n + 1, MAX);
  for (int i = 0; i < (m + 1); i++) dp[i][0] = 0;
  for (int i = 1; i < (m + 1); i++) cin >> coins[i];

  for (int i = 1; i < (m + 1); i++) {
    for (int j = 1; j < (n + 1); j++) {
      if (coins[i] <= j) {
        dp[i][j] = min(dp[i][j-coins[i]] + 1, dp[i-1][j]);
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }

  cout << dp[m][n] << endl;
}
