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
vector<long long> V;

void a(long long v) {
  for (long long i = 1; i*i <= v; i++) {
    if (v % i == 0) {
      V.push_back(i);
      auto t2 = v/i;
      if (t2 != i) {
        V.push_back(t2);
      }
    }
  }
}

int main()
{
  long long N, ans = 0;
  cin >> N;
  a(N);

  for (auto& vi: V) {
    auto m = vi-1;
    if (m != 0 && N%m == N/m) {
      ans += m;
    }
  }

  printf("%lld\n", ans);
  return 0;
}
