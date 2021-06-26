#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int x, y;
  cin >> x >> y;

  if (x == y) {
    cout << x << endl;
    return 0;
  }



  cout << (3 - x -y) << endl;

  return 0;
}
