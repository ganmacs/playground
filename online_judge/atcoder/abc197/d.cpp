#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iostream>
#include <iomanip>

const double PI=3.14159265358979323846;

using namespace std;

int main()
{
  int N, x, y, xn2, yn2;
  cin >> N >> x >> y >> xn2 >> yn2;

  double theta = 2 * PI / N;

  double xx = (x + xn2 + 0.0) / 2.0;
  double yy = (y + yn2 + 0.0) / 2.0;

  double xxx = x - xx;
  double yyy = y - yy;

  double a = (xxx*(double)cos(theta) - yyy*(double)sin(theta) + xx);
  double b = (xxx*sin(theta) + yyy*cos(theta) + yy);

  cout << a*1.0 << " " << b*1.0 << endl;

  return 0;
}
