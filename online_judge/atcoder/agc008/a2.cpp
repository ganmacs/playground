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
  long long x, y;
  cin >> x >> y;

  long long ans = 1e18;

  if (y >= x) ans = min(ans, y-x);
  if (y >= -x) ans = min(ans, y + x + 1);
  if (y <= -x) ans = min(ans, - x - y + 1);
  if (y <= x) ans = min(ans,  x - y + 2);

  cout << ans << endl;

  return 0;
}
