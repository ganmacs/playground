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
  int a, b, c;
  cin >> a >> b >> c;

  if (a == b) {
    cout << c << endl;
  } else if (a == c) {
    cout << b << endl;
  } else if (c == b) {
    cout << a << endl;
  } else {
    cout << 0 << endl;
  }

  return 0;
}
