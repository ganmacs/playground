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

int main()
{
  int X;
  cin >> X;

  int v1 = X/100;

  if (v1*100 <= X && X <= v1*105) {
    cout << 1 << endl;
  } else {
    cout << 0 << endl;
  }

  cout << 0 << endl;
  return 0;
}
