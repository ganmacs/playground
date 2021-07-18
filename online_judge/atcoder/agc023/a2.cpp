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
  int N;
  long long ans = 0;
  cin >> N;
  vector<long long> V(N), D(N + 1, 0);
  for (auto& vi: V) cin >> vi;
  for (int i = 0; i < N; i++) {
    D[i + 1] = D[i] + V[i];
  }
  map<long long, long long> M;
  for (auto& vi: D) M[vi]++;
  for (auto& vi: M) {
    ans += vi.second*(vi.second-1)/2;
  }

  printf("%lld\n", ans);
  return 0;
}
