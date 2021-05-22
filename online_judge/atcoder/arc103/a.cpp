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

  int N, a;
  map<int, int> M1, M2;
  vector<pair<int, int>> V1, V2;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a;
    if (i%2 == 0) {
      M1[a]++;
    } else {
      M2[a]++;
    }
  }

  for (auto& vi: M1) V1.push_back(make_pair(-vi.second, vi.first));
  for (auto& vi: M2) V2.push_back(make_pair(-vi.second, vi.first));
  sort(V1.begin(), V1.end());
  sort(V2.begin(), V2.end());

  if (V1[0].second != V2[0].second) {
    cout << (N + V1[0].first + V2[0].first) << endl;
    return 0;
  } else if (M1.size() == 1 && M2.size() == 1) {
    cout << N/2 << endl;
    return 0;
  }

  int ans = 1e9;
  if (V1.size() >= 2) ans = min(ans, N + V1[1].first + V2[0].first);
  if (V2.size() >= 2) ans = min(ans, N + V2[1].first + V1[0].first);
  cout << ans << endl;

  return 0;
}
