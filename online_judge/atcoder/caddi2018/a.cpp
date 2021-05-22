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
  unsigned long long N, P;
  cin >> N >> P;
  map<unsigned long long, int> M;

  if (N == 1) {
    cout << P << endl;
    return 0;
  }

  if (P == 1) {
    cout << 1 << endl;
    return 0;
  }

  unsigned long long p = P;
  for (unsigned long long i = 2; (i*i) <= P && p > 1; i++) {
    while (p % i == 0) {
      M[i]++;
      p /= i;
    }
  }

  unsigned long long ans = 1;
  for (auto& vi: M) {
    while (vi.second >= N) {
      vi.second -= N;
      ans *= vi.first;
    }
  }

  cout << ans << endl;
  return 0;
}
