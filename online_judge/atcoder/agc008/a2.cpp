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
  long long e = 1e18;

  if (y >= x) e = min(e, y-x);
  if (y >= -x) e = min(e, 1 + y + x);
  if (y <= -x) e = min(e, 1 - x - y);
  if (x > y) e = min(e, 2 + x - y);
  cout << e << endl;

  return 0;
}
