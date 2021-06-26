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

int main()
{
  int N, W, m;
  cin >> N >> W;
  vector<int> w(N), v(N);
  for (int i = 0; i < N; i++) {
    cin >> w[i] >> v[i];
  }

  vector<long long> DP(N*1000 + 1, 1e18);
  DP[0] = 0;

  for (int i = 0; i < N; i++) {
    for (int j = N*1000; j - v[i] >= 0; j--) {
      if (DP[j] > DP[j-v[i]] + w[i]) {
        DP[j] = DP[j-v[i]] + w[i];
      }
    }
  }

  for (int i = N*1000; i >= 0; i--) {
    if (DP[i] <= W) {
      cout << i << endl;
      return 0;
    }
  }

  return 0;
}
