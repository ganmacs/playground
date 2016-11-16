#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;

int main()
{
  int xp0, yp0, xp1, yp1, xp2, yp2, xp3, yp3;
  int in, out;
  int s1x, s1y, s2x, s2y;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> xp0 >> yp0 >> xp1 >> yp1 >> xp2 >> yp2 >> xp3 >> yp3;
    s1x = (xp1 - xp0);
    s1y = (yp1 - yp0);
    s2x = (xp3 - xp2);
    s2y = (yp3 - yp2);

    in = s1x * s2x + s1y * s2y;
    out = s1x * s2y - s1y * s2x;

    if (in == 0) {
      printf("1\n");
    } else if (out == 0) {
      printf("2\n");
    } else {
      printf("0\n");
    }
  }
}
