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
  map<int, unsigned long long> M;
  int N;
  cin >> N;
  vector<int> V(N);

  for (auto& vi: V) {
    cin >> vi;
    M[vi]++;
  };

  unsigned long long ans = 0;
  for (auto& vi: M) {
    if (vi.second >= 2) {
      ans += vi.second * (vi.second - 1) / 2;
    }
  };

  for (int i = 0; i < N; i++) {
    unsigned long long tans = ans;
    unsigned long long t = M[V[i]];
    if (t >= 2) {
      tans -= t * (t-1) / 2;
      tans += (t-2) * (t-1) /2;
    }

    cout << tans << endl;
  }

  return 0;
}
