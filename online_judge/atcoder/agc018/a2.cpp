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
  int N, K;
  cin >> N >> K;
  vector<long long> A(N), A2;
  for (auto& vi: A) cin >> vi;

  long long a = 0;
  bool t = true;
  for (auto& vi: A) {
    if (vi == K) {
      puts("POSSIBLE");
      return 0;
    }

    if (vi > K) {
      A2.push_back(vi-K);
      t = false;
    }
    a = gcd(a, vi);
  }

  if (t) {
    puts("IMPOSSIBLE");
    return 0;
  }

  for (auto& vi: A2) {
    if (vi % a == 0) {
      puts("POSSIBLE");
      return 0;
    }
  }

  puts("IMPOSSIBLE");

  return 0;
}
