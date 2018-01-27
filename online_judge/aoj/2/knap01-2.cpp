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
static const ll INF = 1e+9+1;
static const int MAX = 100 * 100;
ll dp[MAX + 1];

int main()
{
  int N, W;
  cin >> N >> W;

  fill_n(dp, MAX + 1, INF);
  dp[0] = 0;

  int v, w;
  for (int i = 0; i < N; i++) {
    cin >> v >> w;
    for (int j = MAX; j >= v; j--) {
      dp[j] = min(dp[j], dp[j-v] + w);
    }
  }

  for (int i = MAX; i >= 0; i--) {
    if (dp[i] > W) continue;
    cout << i << endl;
    break;
  }
}
