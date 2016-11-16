#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int n;

double dot(double x1, double y1, double x2, double y2) { return (x1 * x2) + (y1 * y2); }
double cross(double x1, double y1, double x2, double y2) { return (x1 * y2) - (y1 * x2); }
double norm(double x, double y) { return (x * x) + (y * y); }
double abs(double x ,double y) { return sqrt(norm(x, y));}
double distance(double x1, double y1, double x2, double y2) { return abs(x2-x1, y2-y1); }
double distance_lp(double x1, double y1, double x2, double y2, double px, double py) {
  return cross(x2 - x1, y2 - y1, px - x1, py - y1) / abs(x2 - x1, y2 - y1);
}

double distance_sp(double x1, double y1, double x2, double y2, double px, double py) {
  if (dot(px - x1, py - y1, x2 - x1, y2 - y1) < 0.0) {
    return abs(px - x1, py - y1);
  }
  if (dot(px - x2, py - y2, x1 - x2, y1 - y2) < 0.0) {
    return abs(px - x2, py - y2);
  }
  return distance_lp(x1, y1, x2, y2, px, py);
}

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
  if (abs(p1x - p0x,  p1y - p0y) < abs(p2x - p0x,  p2y - p0y)) return ONLINE_FRONT;

  return ONLINE_SEGMENT;
}

int main()
{
  int xp0, yp0, xp1, yp1, xp2, yp2;
  cin >> xp0 >> yp0 >> xp1 >> yp1;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> xp2 >> yp2;
    switch(ccw(xp0, yp0, xp1, yp1, xp2, yp2)) {
    case COUNTER_CLOCKWISE:
      printf("COUNTER_CLOCKWISE\n");
      break;
    case CLOCKWISE:
      printf("CLOCKWISE\n");
      break;
    case ONLINE_BACK:
      printf("ONLINE_BACK\n");
      break;
    case ONLINE_FRONT:
      printf("ONLINE_FRONT\n");
      break;
    case ONLINE_SEGMENT:
      printf("ON_SEGMENT\n");
      break;
    }
  }
}
