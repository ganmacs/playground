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

int main()
{
  long long P, a = 1, ans = 0;;
  cin >> P;

  for (int i = 1; i <= 10; i++) a *= i;

  for (int i = 10; i >= 1; i--) {
    while (P >= a) {
      long long t = P/a;
      ans += t;
      P -= t*a;
    }
    a /= i;

    if (P == 0) {
      break;
    }
  }

  cout << ans << endl;

  return 0;
}
