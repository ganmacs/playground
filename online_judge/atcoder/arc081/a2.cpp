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
  int N, a;
  cin >> N;
  map<int, int> M;
  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  }

  vector<long long> T;
  for (auto& vi: M) {
    if (vi.second >= 4) {
      T.push_back(vi.first);
      vi.second -= 2;
    }

    if (vi.second >= 2) {
      T.push_back(vi.first);
      vi.second -= 2;
    }
  }

  if (T.size() < 2) {
    printf("%d\n", 0);
    return 0;
  }

  sort(T.begin(), T.end(), greater<long long>());
  printf("%lld\n", T[0] * T[1]);
  return 0;
}
