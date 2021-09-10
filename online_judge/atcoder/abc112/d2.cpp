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

map<long long, long long> V;

void f(long long a) {
  for (int i = 1; i*i <= a; i++) {
    if (a%i == 0) {
      auto aa = a/i;
      V[i] = aa;
      if (aa != i) {
        V[aa] = i;
      }
    }
  }
}

int main()
{
  long long N, M, ans = 0;
  cin >> N >> M;

  f(M);

  for (auto& vi: V) {
    if (vi.first >= N) {
      ans = max(ans, vi.second);
    }
  }

  printf("%lld\n", ans);

  return 0;
}
