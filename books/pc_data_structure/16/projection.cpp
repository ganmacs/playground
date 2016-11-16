#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;

double dot(int x1, int y1, int x2, int y2) { return (x1 * x2) + (y1 * y2); }
double norm(int x, int y) { return (x * x) + (y * y); }

int main()
{
  int xp1, yp1, xp2, yp2;
  int xp, yp;
  double ss, in;

  cin >> xp1 >> yp1 >> xp2 >> yp2;
  int base_x = xp2 - xp1;
  int base_y = yp2 - yp1;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> xp >> yp;
    in = dot(base_x, base_y, xp - xp1,  yp - yp1);

    ss = in / norm(base_x, base_y);
    printf("%0.10f ", xp1 + base_x * ss);
    printf("%0.10f\n", yp1 + base_y * ss);
  }
}
