#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main()
{
  long long  N, K, ans = 0;
  cin >> N >> K;

  if (K == 0) {
    printf("%lld\n", N*N);
    return 0;
  }

  for (int b = K + 1; b <= N; b++) {
    long long n = N/b;
    ans += n*(b-K) + max((N - n*b - K + 1), 0LL);
  }

  printf("%lld\n", ans);
  return 0;
}
