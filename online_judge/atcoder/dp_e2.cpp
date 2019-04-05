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
long long ans[123456];
int N, W, sum = 0;

int main(int argc, char *argv[])
{
  cin >> N >> W;
  std::fill(ans, ans + 100002, INF);
  for (int i = 0; i < N; i++) {
    cin >> w[i] >> v[i];
    sum += v[i];
  }

  ans[0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = sum; j >= v[i]; j--) {
      ans[j] = min(ans[j], ans[j-v[i]] + w[i]);
    }
  }

  long long ret = -1;
  for (int i = sum; i >= 0; --i) {
    if(ans[i] <= W) {
      ret = i;
      break;
    }
  }

  cout << ret << endl;
  return 0;
}
