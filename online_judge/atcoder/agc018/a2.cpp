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
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;

  long long g = 0;
  long long m = 0;
  for (auto& vi: V) {
    m = max(m, vi);
    g = gcd(vi, g);
  }

  if (K % g != 0 || K > m) {
    puts("IMPOSSIBLE");
  } else {
    puts("POSSIBLE");
  }

  return 0;
}
