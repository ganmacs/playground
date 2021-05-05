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
  if (y >= -x) e = min(e, y + x + 1);
  if (-y >= x) e = min(e, -y - x + 1);
  if (-y >= -x) e = min(e, -y + x + 2);

  cout << e << endl;
  return 0;
}
