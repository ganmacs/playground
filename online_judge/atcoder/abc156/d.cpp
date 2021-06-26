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
  int n, a, b;
  cin >> n >> a >> b;
  long long ans = pow2(2, n) - 1;
  if(ans < 0) ans += L;

  ans -= count(n, a);
  if(ans < 0) ans += L;

  ans -= count(n, b);
  if(ans < 0) ans += L;

  cout << (ans % L) << endl;
  return 0;
}
