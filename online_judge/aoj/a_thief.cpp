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

int dp[1000 + 1][1000 + 1];
int w[1000 + 1], v[1000 + 1];
int n;

int main(){
  int N, W;
  int idx = 0;
  while (cin >> W, W) {
    idx++;
    cin >> N;
    for (int i = 0; i <= N; i++) {
      fill_n(dp[i], 1001, 0);
      v[i] = 0, w[i] = 0;
    }

    for (int i = 1; i <= N; i++)
      scanf("%d,%d", &v[i], &w[i]);

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= W; j++) {
        if (j - w[i] >= 0) {
          dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]);
        } else {
          dp[i][j] = dp[i-1][j];
        }
      }
    }

    printf("Case %d:\n", idx);
    cout << dp[N][W] << endl;
    cout << (lower_bound(dp[N], dp[N] + W + 1, dp[N][W]) - dp[N]) << endl;
  }
}
