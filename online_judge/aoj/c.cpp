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

int main() {
  int N,W;
  cin >> N >> W;
  vector<int> dp(W+1,0);
  int dp2[101][MAX];

  for(int i=0; i<N; i++) {
    int v,w,m;
    cin >> v >> w >> m;

    for(int k=0; m>0; k++) {
      int num = min(m, (1<<k));
      m -= num;
      int wk = num*w;
      int vk = num*v;
      for(int j=W; j >= num*w; j--)
        dp2[i + 1][j] = max(max(dp2[i + 1][j-wk] + vk, dp2[i][j]), max(dp2[i][j], dp2[i][j-wk] + vk));
      // dp[j] = max(dp[j], dp[j-num*w] + num*v);
    }
  }


  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <=  W; j++) {
      cout << dp2[i][j] << " ";
    }
    cout << endl;
  }

  // for (int i = 0; i <= W; i++) {
  //   cout << dp[i] << " ";
  // }
  cout << endl;
  // cout << ans << endl;
  return 0;
}
