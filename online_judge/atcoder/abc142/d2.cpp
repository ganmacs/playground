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
  unsigned long long a = gcd(A, B);

  long long ans = 1;

  for (unsigned long long i = 2; i*i <= a && a > 1; i++) {
    if (a % i != 0) continue;

    while (a % i == 0) {
      a /= i;
    }
    ans++;
  }

  if (a > 1) {
    ans++;
  }

  cout << ans << endl;
  return 0;
}
