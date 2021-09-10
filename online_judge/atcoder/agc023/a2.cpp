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
  map<long long, long long> M;
  int N;
  long long ans = 0;
  cin >> N;
  vector<long long> V(N), V2(1, 0);
  for (auto& vi: V) cin >> vi;
  M[0] = 1;
  for (int i = 0; i < N; i++) {
    V2.push_back(V[i] + V2.back());
    M[V2.back()]++;
  }

  for (auto& vi: M) {
    if (vi.second >= 2) {
      ans += vi.second*(vi.second-1)/2;
    }
  }

  printf("%lld\n", ans);
  return 0;
}
