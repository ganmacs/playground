#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int n;

double dot(int x1, int y1, int x2, int y2) { return (x1 * x2) + (y1 * y2); }
double cross(int x1, int y1, int x2, int y2) { return (x1 * y2) - (y1 * x2); }
double norm(int x, int y) { return (x * x) + (y * y); }
double abs(int x ,int y) { return sqrt(norm(x, y));}
double distance(int x1, int y1, int x2, int y2) { return abs(x2-x1, y2-y1); }
double distance_lp(int x1, int y1, int x2, int y2, int px, int py) {
  return cross(x2 - x1, y2 - y1, px - x1, py - y1) / abs(x2 - x1, y2 - y1);
}

double distance_sp(int x1, int y1, int x2, int y2, int px, int py) {
  if (dot(px - x1, py - y1, x2 - x1, y2 - y1) < 0.0) {
    return abs(px - x1, py - y1);
  }
  if (dot(px - x2, py - y2, x1 - x2, y1 - y2) < 0.0) {
    return abs(px - x2, py - y2);
  }
  return distance_lp(x1, y1, x2, y2, px, py);
}

double distance_sp(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  // if (intersect()) {
  // }
  // min(distance_sp()
// )

  return 0.0
}

int main()
{

  cin >> n;
  int xp0, yp0, xp1, yp1, xp2, yp2, xp3, yp3;

  for (int i = 0; i < n; i++) {
    cin >> xp0 >> yp0 >> xp1 >> yp1 >> xp2 >> yp2 >> xp3 >> yp3;
    printf("%0.10f\n", distance_sp(xp0, yp0, xp1, yp1, xp2, yp2, xp3, yp3))
  }
}
