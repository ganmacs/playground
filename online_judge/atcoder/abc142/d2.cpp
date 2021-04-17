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
  unsigned long long A, B;
  cin >> A >> B;
  unsigned long long g = gcd(A, B);
  unsigned long long ans = 1;

  for (unsigned long long i = 2; i*i <= g; i++) {
    if (g % i != 0) continue;
    while (g % i == 0) g /= i;
    ans++;
  }

  if (g != 1) ans++;

  cout << ans << endl;

  return 0;
}
