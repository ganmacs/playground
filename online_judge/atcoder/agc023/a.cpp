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
  vector<long long> A(N), B(N + 1);
  for (auto& vi: A) cin >> vi;

  B[0] = 0;
  for (int i = 0; i < N; i++) {
    B[i + 1] = B[i] + A[i];
  }

  map<long long, long long> M;
  for (auto& vi: B) M[vi]++;
  for (auto& vi: M) {
    auto v = vi.second;
    // nC2
    ans += (v * (v-1) / 2 * 1);
  }

  printf("%lld\n", ans);
  return 0;
}
