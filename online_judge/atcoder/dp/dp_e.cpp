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

const long long INF = 1e9;
int v[123456], w[123456];
long long ans[105][123456];
int N, W;

int main(int argc, char *argv[])
{
  cin >> N >> W;
  int sum = 0;

  std::fill(ans[0], ans[0] + 100002, INF);
  for (int i = 1; i <= N; i++) {
    std::fill(ans[i], ans[i] + 100002, INF);
    cin >> w[i] >> v[i];
    sum += v[i];
  }

  ans[0][0] = 0;
  for (int i = 1; i <= N; i++) {
    ans[i][0] = 0;
    for (int j = 1; j <= 100000; j++) {
      if (j >= v[i]) {
        ans[i][j] = min(ans[i-1][j], ans[i-1][j-v[i]] + w[i]);
      } else {
        ans[i][j] = ans[i-1][j];
      }
    }
  }

  long long ret=-1;
  for (int i = sum; i >= 0; --i) {
    if(ans[N][i] <= W) {
      ret = i;
      break;
    }
  }

  cout << ret << endl;
  return 0;
}
