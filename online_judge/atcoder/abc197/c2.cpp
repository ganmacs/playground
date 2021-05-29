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
  int N;
  cin >> N;
  long long ans = 1e18;
  vector<int> V(N);
  for (auto& vi: V) cin >> vi;

  for (int i = 1; i < pow(2, N); i++) {
    long long ta = 0, t2 = 0;
    for (int j = 0; j < N; j++) {
      if ((1 << j) & i) {
        ta ^= t2;
        t2 = V[j];
      } else {
        t2 |= V[j];
      }
    }

    ans = min(ans, t2 ^ ta);
  }

  cout << ans << endl;
  return 0;
}
