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
  long long t;
  vector<long long> L(1, 0), R(1, 0);

  for (int i = 0; i < N; i++) {
    cin >> t;
    if (t < 0) {
      L.push_back(-t);
    } else {
      R.push_back(t);
    }
  }
  sort(L.begin(), L.end());

  long long ans = 1e18;
  for (int i = 0; i < R.size(); i++) {
    if (K - i < L.size()) {
      ans = min(2*R[i] + L[K-i], ans);
    }
  }

  for (int i = 0; i < L.size(); i++) {
    if (K - i < R.size()) {
      ans = min(2*L[i] + R[K-i], ans);
    }
  }

  printf("%lld\n", ans);
  return 0;
}
