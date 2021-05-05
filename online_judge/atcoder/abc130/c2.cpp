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

  cout << (W*H/2.0) << " " << (W == x*2 && H == y*2) << endl;
  return 0;
}
