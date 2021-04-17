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
  int N, x0, y0, xn2, yn2;
  cin >> N;
  cin >> x0 >> y0 >> xn2 >> yn2;

  double xx = (x0 + xn2)/2.0;
  double yy = (y0 + yn2)/2.0;
  double r = 2*PI/N;

  double xxx = (x0-xx)*cos(r) - (y0-yy)*sin(r) + xx;
  double yyy = (x0-xx)*sin(r) + (y0-yy)*cos(r) + yy;

  printf("%08f %08f\n", xxx, yyy);
  return 0;
}
