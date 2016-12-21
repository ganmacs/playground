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
typedef long long ll;
static const ll INF = 1000000000;
static const int MAX = 100000;

int N;
ll dp[MAX];

int main() {
  cin >> N;
  fill_n(dp, N, INF);

  ll v;
  for (int i = 0; i < N; i++) {
    cin >> v;
    *lower_bound(dp, dp + N, v) = v;
  }

  cout << (lower_bound(dp, dp + N, INF) - dp) << endl;
}
