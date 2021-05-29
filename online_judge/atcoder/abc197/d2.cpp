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

static const double PI = 3.141592653589793;

int main()
{
  long long N, x0, y0, x1, y1;
  cin >> N >> x0 >> y0 >> x1 >> y1;
  double t = (360/N)*(PI/180);

  double xx = ((double)(x0 + x1))/2.0;
  double yy = ((double)(y0 + y1))/2.0;

  double xp = (x0-xx);
  double yp = (y0-yy);

  double x = xp*(double)cos(t) - yp*(double)sin(t) + xx;
  double y = xp*(double)sin(t) + yp*(double)cos(t) + yy;

  cout << x*1.0 << " " << y*1.0 << endl;
  return 0;
}
