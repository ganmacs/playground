#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;

double dot(double x1, double y1, double x2, double y2) { return (x1 * x2) + (y1 * y2); }
double cross(double x1, double y1, double x2, double y2) { return (x1 * y2) - (y1 * x2); }
double norm(double x, double y) { return (x * x) + (y * y); }
double aabs(double x ,double y) { return sqrt(norm(x, y));}

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ONLINE_SEGMENT = 0;
static const double EPS = 1e-8;

int ccw(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y){
  double c = cross(p1x - p0x,  p1y - p0y, p2x - p0x,  p2y - p0y);
  double d = dot(p1x - p0x,  p1y - p0y, p2x - p0x,  p2y - p0y);

  if (c > EPS) return COUNTER_CLOCKWISE;
  if (c < -EPS) return CLOCKWISE;
  if (d < -EPS) return ONLINE_BACK;
  if (aabs(p1x - p0x,  p1y - p0y) < aabs(p2x - p0x,  p2y - p0y)) return ONLINE_FRONT;

  return ONLINE_SEGMENT;
}

bool intersection(int xp0, int yp0, int xp1, int yp1, int xp2, int yp2, int xp3, int yp3)
{
  int a = ccw(xp0, yp0, xp1, yp1, xp2, yp2);
  int b = ccw(xp0, yp0, xp1, yp1, xp3, yp3);
  int c = ccw(xp2, yp2, xp3, yp3, xp0, yp0);
  int d = ccw(xp2, yp2, xp3, yp3, xp1, yp1);

  return (a * b <= 0 && c * d <= 0);
}

double distance(double x1, double y1, double x2, double y2) { return aabs(x2 - x1, y2 - y1); }
double distance_lp(double x1, double y1, double x2, double y2, double px, double py) {
  return std::abs(cross(x2 - x1, y2 - y1, px - x1, py - y1) / aabs(x2 - x1, y2 - y1));
}

double distance_sp(double x1, double y1, double x2, double y2, double px, double py) {
  if (dot(px - x1, py - y1, x2 - x1, y2 - y1) < 0.0) {
    return aabs(px - x1, py - y1);
  }
  if (dot(px - x2, py - y2, x1 - x2, y1 - y2) < 0.0) {
    return aabs(px - x2, py - y2);
  }
  return distance_lp(x1, y1, x2, y2, px, py);
}

double distance_sp(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
  if (intersection(x1, y1, x2, y2, x3, y3, x4, y4)) return 0.0;
  return min(min(distance_sp(x1, y1, x2, y2, x3, y3), distance_sp(x1, y1, x2, y2, x4, y4)),
             min(distance_sp(x3, y3, x4, y4, x1, y1), distance_sp(x3, y3, x4, y4, x2, y2)));
}

int main()
{
  cin >> n;
  int xp0, yp0, xp1, yp1, xp2, yp2, xp3, yp3;

  for (int i = 0; i < n; i++) {
    cin >> xp0 >> yp0 >> xp1 >> yp1 >> xp2 >> yp2 >> xp3 >> yp3;
    printf("%0.10f\n", distance_sp(xp0, yp0, xp1, yp1, xp2, yp2, xp3, yp3));
  }
}
