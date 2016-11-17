#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;

double dot(int x1, int y1, int x2, int y2) { return (x1 * x2) + (y1 * y2); }
double norm(int x, int y) { return (x * x) + (y * y); }

pair<double, double> project(double xp1, double yp1, double xp2, double yp2, double xp, double yp)
{
  int base_x = xp2 - xp1;
  int base_y = yp2 - yp1;

  double in = dot(base_x, base_y, xp - xp1,  yp - yp1);
  double ss = in / norm(base_x, base_y);
  return make_pair(xp1 + base_x * ss, yp1 + base_y * ss);
}

int main()
{
  int xp1, yp1, xp2, yp2;
  int xp, yp;
  cin >> xp1 >> yp1 >> xp2 >> yp2;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> xp >> yp;
    pair<double, double> d = project(xp1, yp1, xp2, yp2, xp, yp);
    printf("%0.10f %0.10f\n", d.first, d.second);
  }
}
