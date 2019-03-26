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
  int a[3];
  cin >> a[0] >> a[1] >> a[2];
  sort(a, a + 3);

  int d1 = a[2] - a[0];
  int d2 = a[2] - a[1];

  if ((a[2]*2 - d1 - d2) % 2) {
    cout << (a[2]*2 - d1 - d2) / 2 + 2 << endl;
  } else {
    cout << (a[2]*2 - d1 - d2) / 2 << endl;
  }

  return 0;
}
