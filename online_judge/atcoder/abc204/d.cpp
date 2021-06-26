#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int D[112345];

int main()
{
  int N;
  long long t = 0;
  cin >> N;
  vector<long long> V(N);
  for (auto& vi: V) {
    cin >> vi;
    t += vi;
  }

  fill(D, D + t + 1, 0);
  D[0] = 1;

  for (auto& vi: V) {
    for (int i = t; i >= vi; i--) {
      if (D[i-vi]) {
        D[i] = 1;
      }
    }
  }

  long long ans = 1e9;
  for (long long i = 1; i <= t; i++) {
    if (D[i]) {
      ans = min(max(i, t-i), ans);
    }
  }

  cout << ans << endl;
  return 0;
}
