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
#include <numeric>

using namespace std;

unsigned long long d[112345];

int main()
{
  unsigned long long N, K, ans = 0;;
  cin >> N >> K;
  vector<unsigned long long> V(N);

  d[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> V[i];
    d[i + 1] = V[i] + d[i];
  }

  for (int i = 0; i <= N; i++) {
    int ok = i, ng = N + 1;
    while (ng - ok > 1) {
      int p = (ok + ng) / 2;
      if (d[p] < K) {
        ok = p;
      } else {
        ng = p;
      }
    }

    K -= d[i];
    K += d[i + 1];
    ans += (N-(ng-1));
  }

  cout << ans << endl;

  return 0;
}
