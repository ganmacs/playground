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

int main()
{
  long long x, y, ans = 1e18;
  cin >> x >> y;

  if (x == -y) {
    ans = min(ans, (long long)1);
  }

  if (y > x) {
    ans = min(ans, y-x);
  }

  if (y > -x) {
    ans = min(ans, 1 + y + x);
  }

  if (y < -x) {
    ans = min(ans, -x - y + 1);
  }

  if (x > y) {
    ans = min(ans, x - y + 2);
  }

  cout << ans << endl;
  return 0;
}
