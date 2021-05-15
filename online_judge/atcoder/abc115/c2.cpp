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

int main()
{
  int N, K;
  cin >> N >> K;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };
  sort(V.begin(), V.end());

  long long ans = 1e18;
  for (int i = 0; (i + K - 1) < N; i++) {
    ans = min(ans, (long long)(V[K + i - 1] - V[i]));
  }

  cout << ans << endl;
  return 0;
}
