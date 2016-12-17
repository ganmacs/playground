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
static const int MAX = 10000;

int v[100], w[100], m[100];
int dp[MAX + 1];

int main()
{
  int N, W;
  cin >> N >> W;
  int v, w, m;

  for (int i = 0; i < N; i++) {
    cin >> v >> w >> m;
    for (int k = 0; m > 0; k++) {
      int num = min(m, 1 << k);
      m -= num;
      int wk = num*w;
      int vk = num*v;
      for (int j = W; j >= wk; j--) {
        dp[j] = max(dp[j], dp[j-wk] + vk);
      }
    }
  }

  int mm = 0;
  for (int i = 0; i <= W; i++) {
    mm = max(mm, dp[i]);
  }
  printf("%d\n", mm);
}
