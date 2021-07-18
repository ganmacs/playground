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

void a(long long n) {
  for (long long i = 1; i*i <= n; i++) {
    if (n % i == 0) {
      V.push_back(i);
      auto t = n/i;
      if (t != i) {
        V.push_back(t);
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
    long long m = vi-1;
    if (m > 0 && N%m == N/m) {
      ans += m;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
