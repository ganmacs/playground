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

int v[123456], w[123456];
long long ans[105][123456];
int N, W;

int main(int argc, char *argv[])
{
  cin >> N >> W;

  std::fill(ans[0], ans[0] + W, 0);
  for (int i = 1; i <= N; i++) {
    cin >> w[i] >> v[i];
    ans[i][0] = 0;
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= W; j++) {
      if (j < w[i]) {
        ans[i][j] = ans[i-1][j];
      } else {
        ans[i][j] = max(ans[i][j-w[i]], max(ans[i-1][j], ans[i-1][j-w[i]] + v[i]));
      }
    }
  }

  cout << ans[N][W] << endl;
  return 0;
}
