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
  int A, B, C, X, Y, minv = 1000000000;
  cin >> A >> B >> C >> X >> Y;


  for (int i = 0; i <=  100000; i++) {
    int x = max(0, X - i/2);
    int y = max(0, Y - i/2);
    minv = min(minv, x*A + y*B + i*C);
  }

  printf("%d\n", minv);
  return 0;
}
