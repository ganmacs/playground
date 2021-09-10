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

vector<long long> V(1, 1), P(1, 1);

long long f(long long n, long long x) {
  if (n == 0) {
    if (x <= 0) return 0;
    return 1;
  }

  auto m = V[n-1] + 2;
  if (m == x) {
    return P[n-1] + 1;
  } else if (m < x) {
    return f(n-1, x-m) + P[n-1] + 1;
  } else {
    return f(n-1, x-1);
  }
}

int main()
{
  long long N, X;
  cin >> N >> X;
  for (int i = 1; i <= N; i++) V.push_back(2*V[i-1] + 3);
  for (int i = 1; i <= N; i++) P.push_back(2*P[i-1] + 1);

  printf("%lld\n", f(N, X));
  return 0;
}
