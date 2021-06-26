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
  int N, H, a, b;
  cin >> N >> H;
  vector<pair<int, bool>> V;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    V.push_back({-a, true});
    V.push_back({-b, false});
  }
  sort(V.begin(), V.end());

  int ans = 0;
  for (auto& vi: V) {
    vi.first = -vi.first;

    if (vi.second) {
      ans += (H / vi.first);
      ans += ((H % vi.first) != 0 ? 1 : 0);
      H = 0;
    } else {
      H -= vi.first;
      ans++;
    }

    if (H <= 0) break;
  }

  cout << ans << endl;
  return 0;
}
