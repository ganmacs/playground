#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

int
main()
{
  int N, a;
  cin >> N;
  map<int, int> V;
  set<int> s;

  for (int i = 0; i < N; i++) {
    cin >> a;
    V[a]++;
  }

  int ans = 0;
  for (auto& vi: V) {
    if (vi.first == vi.second) {
      continue;
    } else if (vi.second > vi.first) {
      ans += (vi.second - vi.first);
    } else {
      ans += vi.second;
    }
  };

  cout << ans << endl;
  return 0;
}
