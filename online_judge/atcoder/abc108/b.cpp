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

using namespace std;

int main(int argc, char *argv[])
{
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  int xx = x2-x1;
  int yy = y2-y1;

  cout << (x2 - yy) << " " << (y2 + xx) << " " << (x1-yy) << " " << (y1 + xx);


  return 0;
}
