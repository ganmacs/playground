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
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  if (a < c) {
    cout << max(0, (min(b, d) - c)) << endl;
  } else {
    cout << max(0, (min(b, d) - a)) << endl;
  }

  return 0;
}
