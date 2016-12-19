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
static const int INF = 1000000;
static const int MAX = 100000;
int dp[MAX + 10];

int main()
{
  int N, M;
  cin >> N >> M;

  fill_n(dp, N + 1, INF);
  dp[0] = 0;

  int v;
  for (int i = 0; i < M; i++) {
    cin >> v;

    for (int j = 0; j <= N; j++) {
      if (j - v >= 0) {
        dp[j] = min(dp[j], dp[j-v] + 1);
      }
    }
  }

  cout << dp[N] << endl;
}
