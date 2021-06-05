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

int main() {
  int N, a;
  cin >> N;
  map<int, int> M1, M2;
  vector<pair<long long, long long>> VV1, VV2;

  for (int i = 0; i < N; i++) {
    cin >> a;
    if (i % 2) {
      M1[a]++;
    } else {
      M2[a]++;
    }
  }

  for (auto& vi: M1) VV1.push_back({ -vi.second, vi.first });
  for (auto& vi: M2) VV2.push_back({ -vi.second, vi.first });
  sort(VV1.begin(), VV1.end());
  sort(VV2.begin(), VV2.end());

  if (VV1.size() == 1 && VV2.size() == 1) {
    if (VV1[0].second == VV2[0].second) {
      cout << N + VV1[0].first << endl;
    } else {
      cout << 0 << endl;
    }
    return 0;
  }

  long long ans = 1e18;
  if (VV1[0].second == VV2[0].second) {
    if (VV1.size() > 1) ans = min(ans, N + VV1[1].first + VV2[0].first);
    if (VV2.size() > 1) ans = min(ans, N + VV2[1].first + VV1[0].first);
  } else {
    ans = N + VV1[0].first + VV2[0].first;
  }
  cout << ans << endl;
  return 0;
}
