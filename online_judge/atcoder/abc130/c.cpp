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
  int W, H, x, y, a = 0;
  cin >> W >> H >> x >> y;

  if (x*2 == W && y*2 == H) {
    a = 1;
  } else {
    a = 0;
  }

  printf("%.9f %d\n", double(H)*double(W)/2, a);
  return 0;
}
