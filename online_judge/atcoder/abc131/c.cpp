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

unsigned long long int gcd(unsigned long long int x, unsigned long long int y) {
  if(x < y) swap(x, y);

  while (y > 0) {
    unsigned long long int r = x % y;
    x = y;
    y = r;
  }
  return x;
}

int main()
{
  unsigned long long int A, B, ans = 0;;
  int C, D;
  cin >> A >> B >> C >> D;

  if (C == 1 || D == 1) {
    cout << 0 << endl;
    return 0;
  }

  ans = (B/C) - ((max(A-1, 1ULL))/C);
  ans += (B/D) - ((max(A-1, 1ULL))/D);
  unsigned long long int v = (unsigned long long)abs(C) / gcd(C, D) * (unsigned long long)abs(D);
  ans -= (B/v) - ((max(A-1, 1ULL))/v);

  cout << B - A + 1 - ans << endl;
  return 0;
}
