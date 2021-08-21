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
  map<int, long long> A, B, C;
  long long N, a;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> a;
    if (i % 2 == 0) {
      A[a]--;
    } else {
      B[a]--;
    }

    C[a]++;
  }

  if (C.size() == 1) {
    printf("%lld\n", C[a]/2);
    return 0;
  }

  vector<pair<long long, int>> A2, B2;

  for (auto& vi: A) A2.push_back({ vi.second, vi.first });
  for (auto& vi: B) B2.push_back({ vi.second, vi.first });
  sort(A2.begin(), A2.end());
  sort(B2.begin(), B2.end());

  if (A2[0].second != B2[0].second) {
    printf("%lld\n", N + A2[0].first + B2[0].first);
  } else {
    long long t = 1e18;
    if (A2.size() > 1) t = min(t, A2[1].first + B2[0].first);
    if (B2.size() > 1) t = min(t, B2[1].first + A2[0].first);
    printf("%lld\n", N + t);
  }

  return 0;
}
