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

long long L = 1e9 + 7;

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
  int X, Y;
  long long ans = 0;
  cin >> X >> Y;

  for (int b = 0; b <= 1e6; b++) {
    if (((Y - b)%2) != 0) continue;
    if (Y -b < 0) continue;
    int a = (Y - b)/2;

    if ((Y == 2*a + b) && (X == a + 2*b)) {
      ans += count(a + b, min(a, b));
    }
  }

  cout << ans << endl;

  return 0;
}
