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
  long long ans = 0;
  long long N, K;
  cin >> N >> K;

  if (K == 0) {
    printf("%lld\n", N*N);
    return 0;
  }

  for (long long b = K + 1; b <= N; b++) {
    long long n = (N + 1)/b;
    ans += n*(b-K);
    ans += max(0LL,  N-n*b-K + 1);
  }

  printf("%lld\n", ans);

  return 0;
}
