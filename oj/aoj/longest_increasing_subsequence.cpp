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
static const int MAX = 100000;
static const int INF = 1000000000;

int v[MAX + 1];
int dp[MAX + 1];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    v[i]--;
  }

  fill_n(dp, n + 1, INF);
  for (int i = 0; i < n; i++) {
    *lower_bound(dp, dp + n, v[i]) = v[i];
  }
  cout << (lower_bound(dp, dp + n, INF)-dp) << endl;
}
