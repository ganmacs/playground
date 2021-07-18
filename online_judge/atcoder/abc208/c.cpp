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

int main()
{
  unsigned long long N, K;
  cin >> N >> K;
  vector<unsigned long long> V(N);
  map<unsigned long long, unsigned long long> M;

  unsigned long long t = K/N;
  unsigned long long ta = K%N;

  for (auto& vi: V) {
    cin >> vi;
    M[vi] = t;
  }

  for (auto& vi: M) {
    if (ta == 0) break;
    vi.second++;
    ta--;
  }

  for (auto& vi: V) {
    cout << M[vi] << endl;
  }

  return 0;
}
