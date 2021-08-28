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

int main()
{
  int N, ans = 0;
  long long X, L;
  vector<pair<long long, long long>> V;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> X >> L;
    V.push_back({X + L, X - L});
  }
  sort(V.begin(), V.end());
  long long t = -1e18;
  for (auto& vi: V) {
    auto r = vi.first, l = vi.second;
    if (l < t) {
      ans++;
    } else {
      t = r;
    }
  }

  printf("%d\n", N-ans);
  return 0;
}
