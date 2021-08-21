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
  int N, K;
  cin >> N >> K;
  long long ans = 0;
  for (int b = K + 1; b <= N; b++) {
    long long t = b-K;
    long long n = N/b;
    long long rest = N%b;
    long long tt = rest - K;
    if (K != 0) tt++;
    ans += n*t + max(0LL, tt);
  }
  printf("%lld\n", ans);
  return 0;
}
