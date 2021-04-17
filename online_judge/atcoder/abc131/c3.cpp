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
  unsigned long long A, B, C, D;
  cin >> A >> B >> C >> D;
  unsigned long long k = lcm(C, D);
  unsigned long long k1 = B/C - (A-1)/C;
  unsigned long long k2 = B/D - (A-1)/D;
  unsigned long long k3 = B/k - (A-1)/k;
  unsigned long long ans = B - A + 1 - (k1 + k2 - k3);
  cout << ans << endl;

  return 0;
}
