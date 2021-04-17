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
  int W, H, x, y;
  cin >> W >> H >> x >> y;

  double a1 = min(W-x, x)*H*1.0;
  double a2 = min(H-y, y)*W*1.0;
  printf("%.9f %d\n", double(H)*double(W)/2, x*2 == W && y*2 == H);
  return 0;
}
