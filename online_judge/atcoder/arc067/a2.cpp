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

const int L = 1000000007;

map<long long, long long> M;

void prim(long long t) {
  int i = 2;
  while (t > 1) {
    while (t % i == 0) {
      M[i]++;
      t /= i;
    }
    i++;
  }
}

int main()
{
  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    prim(i);
  }

  long long ans = 1;
  for (auto& vi: M) {
    ans = (ans * (vi.second + 1)) % L;
  }

  printf("%lld\n", ans);
  return 0;
}
