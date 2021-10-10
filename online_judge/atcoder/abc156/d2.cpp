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


const long long L = 1000000007;

long long pow2(long long x, long long n)
{
  long long ans = 1;
  while (n > 0) {
    if (n & 1) ans = ans * x % L;
    x = x * x % L;
    n >>= 1;
  }

  return ans;
}

long long modinv(long long a) {
  return pow2(a, L - 2);
}

long long count(long long n, long long k) {
  long long res = 1;
  for (long long i = 0; i < k; i++) {
    res = (res * (n - i)) % L;
  }

  long long res2 = 1;
  for (long long i = 1; i <= k; i++) {
    res2 = (res2 * i) % L;
  }

  res = res * modinv(res2) % L;
  return res;
}


int main()
{
  return 0;
}
