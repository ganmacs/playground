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
#include <numeric>

using namespace std;

int main()
{
  double W, H, x, y;
  cin >> W >> H >> x >> y;

  int k = (W/2 == x) && (H/2 == y);
  cout << W*H/2.0 << " " << k << endl;
  return 0;
}
