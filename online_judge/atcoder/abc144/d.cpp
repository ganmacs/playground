#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

int
main()
{
  const double PI = 3.14159265358979323846;
  double a, b, x;
  cin >> a >> b >> x;
  x /= a;

  cout << fixed << setprecision(10);
  if (a*b/2 < x) {
    cout << atan2((a*b - x)*2, a*a) * 180 / PI << endl;
  } else {
    cout << atan2(b*b, 2*x) * 180 / PI << endl;
  }
  return 0;
}
